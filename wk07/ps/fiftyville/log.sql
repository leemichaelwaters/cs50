-- Keep a log of any SQL queries you execute as you solve the mystery.


-- Find crime scene description
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';
-- Theft took place at 10:15am at Humphrey Street bakery
-- Interviews with three witnesses
-- Littering took place at 16:36 with no witnesses


-- Find three witness interviews
SELECT *
FROM interviews
WHERE month = 7 AND day = 28
AND transcript LIKE '%bakery%';
-- Ruth: Within 10 min of theft, thief got into car in bakery parking lot and drove away
-- Euguene: Thief withdrew money same day before crime on Leggett Street
-- Raymond: Thief planning to take earliest flight out of Fiftyville next day. Asked other person on phone to purchase flight ticket.


-- Get more info on flights
SELECT *
FROM flights
WHERE day = 29
LIMIT 10;
-- Earliest flight is id 36


-- Identify suspect
SELECT DISTINCT *
FROM people
-- Joins
-- #1
JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate
-- #2
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON bank_accounts.account_number = atm_transactions.account_number
-- #3
JOIN passengers
ON people.passport_number = passengers.passport_number
JOIN flights
ON passengers.flight_id = flights.id
JOIN phone_calls
on people.phone_number = phone_calls.caller
-- Witness criteria
-- #1
WHERE bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute > 15 AND bakery_security_logs.minute <= 25
-- #2
AND atm_transactions.transaction_type = 'withdraw'
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.atm_location = 'Leggett Street'
-- #3
AND passengers.flight_id = 36
AND phone_calls.month = 7
AND phone_calls.day = 28;
-- Bruce


-- Determine accomplice
SELECT name
FROM people
WHERE phone_number = '(375) 555-8161';
-- Robin


-- Determine location
SELECT *
FROM airports
WHERE id = 4;
-- New York City