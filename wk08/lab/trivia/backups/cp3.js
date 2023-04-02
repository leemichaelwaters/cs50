// TODO: Re-factor code
// TODO: Text should appear beneath the question


document.addEventListener('DOMContentLoaded', function() {


    // Alert incorrect
    document.querySelector('#red1').addEventListener('click', function() {
        alert('Incorrect');
        event.preventDefault();
    });

    document.querySelector('#red2').addEventListener('click', function() {
        alert('Incorrect');
        event.preventDefault();
    });


    // Alert correct
    document.querySelector('#green').addEventListener('click', function() {
        alert('Correct!');
        event.preventDefault();
    });


    // Turn buttons red
    let rb1 = document.querySelector('#red1');
    document.querySelector('#red1').addEventListener('click', function() {
        rb1.style.backgroundColor = 'red';
    });

    let rb2 = document.querySelector('#red2');
    document.querySelector('#red2').addEventListener('click', function() {
        rb2.style.backgroundColor = 'red';
    });


    // Turn button green
    let gb = document.querySelector('#green');
    document.querySelector('#green').addEventListener('click', function() {
        gb.style.backgroundColor = 'green';
    });


    // Check question two
    document.querySelector('form').addEventListener('submit', function(event) {
        let answer = document.querySelector('#question').value;
        let input = document.querySelector('#question');

        // Handle incorrect answer
        // Text field turn red and text says "Incorrect"
        if (answer != 'Canada')
        {
            alert('Incorrect');
            input.style.backgroundColor = 'red';
        }

        // Handle correct answer
        // Input field turn green and text says "Correct!"
        else
        {
            alert('Correct!');
            input.style.backgroundColor = 'green';
        }
        event.preventDefault();
    });


});