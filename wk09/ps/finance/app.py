import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Display the entries in the database on index.html
    portfolio = db.execute(
        "SELECT symbol, name, sum(shares) AS shares FROM purchases WHERE user_id = ? GROUP BY symbol HAVING sum(shares) > 0", session["user_id"])
    cash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]['cash']
    total = cash  # set total equal to cash holdings
    for stock in portfolio:
        quote = lookup(stock["symbol"])
        stock["price"] = quote["price"]
        stock["subtotal"] = stock["price"] * stock["shares"]
        total += stock["subtotal"]  # add stock subtotal for each stock

    return render_template("index.html", portfolio=portfolio, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached via GET, display form to buy a stock
    if request.method == "GET":
        return render_template("buy.html")

    # User reached via POST, purchase stock
    else:
        # Confirm stock symbol valid
        if not lookup(request.form.get("symbol")):
            return apology("invalid symbol")

        # Confirm number of shares
        elif not request.form.get("shares"):
            return apology("missing shares")

        # Confirm shares is positive int
        # Even though HTML handles this, check with Python too
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("shares must be integer, 400")

        if shares < 0:
            return apology("shares must be positive, 400")

        # Confirm user can afford it
        symbol = request.form.get("symbol").upper()
        quote = lookup(symbol)
        name = quote["name"]
        price = quote["price"]
        cost = shares * price
        # Balance returns rows of dictionary
        balance = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]['cash']
        if cost > balance:
            return apology("can't afford")

        # Update balance and record transaction
        else:
            new_balance = balance - cost
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])
            db.execute("INSERT INTO purchases (user_id, symbol, name, shares, price, cost) VALUES (?, ?, ?, ?, ?, ?)",
                       session["user_id"], symbol, name, shares, price, cost)

        flash('Bought!')
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Display the entries in the database on index.html
    transactions = db.execute("SELECT symbol, shares, price, timestamp FROM purchases WHERE user_id = ?", session["user_id"])

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        return render_template("quote.html")
    else:
        quote = lookup(request.form.get("symbol"))
        if quote:
            return render_template("quoted.html", name=quote["name"], price=quote["price"], symbol=quote["symbol"])
        else:
            return apology("invalid symbol")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "GET":
        return render_template("register.html")
    else:
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure username not taken
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(rows) == 1:
            return apology("username already exists", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation", 400)

        # Ensure passwords match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match", 400)

        # Add user to database
        username = request.form.get("username")
        hash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)

        # Log user in
        user_id = db.execute("SELECT * FROM users WHERE username = ? AND hash = ?", username, hash)[0]["id"]
        session["user_id"] = user_id

        # Redirect user to home page
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Query portfolio to get list of dicts of stocks and shares
    portfolio = db.execute(
        "SELECT symbol, name, sum(shares) AS shares FROM purchases WHERE user_id = ? GROUP BY symbol HAVING sum(shares) > 0", session["user_id"])

    if request.method == "GET":
        return render_template("sell.html", portfolio=portfolio)

    else:
        # User fails to select a stock
        if not request.form.get("symbol"):
            return apology("missing symbol", 400)

        # User fails to input a number of shares
        elif not request.form.get("shares"):
            return apology("missing shares", 400)

        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        # Loop over stocks
        for stock in portfolio:
            # If selected stock, check if there are enough shares
            if (symbol == stock['symbol'] and (shares > stock['shares'])):
                return apology("too many shares", 400)

        # Confirm user can afford it
        quote = lookup(symbol)
        name = quote["name"]
        price = quote["price"]
        cost = shares * price
        # Balance returns rows of dictionary
        balance = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]['cash']

        # Update balance and record transaction
        new_balance = balance + cost

        # Sell shares
        shares = shares * -1

        # Update SQL tables
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])
        db.execute("INSERT INTO purchases (user_id, symbol, name, shares, price, cost) VALUES (?, ?, ?, ?, ?, ?)",
                   session["user_id"], symbol, name, shares, price, cost)

        flash('Sold!')
        return redirect("/")