-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street = 'Chamberlin Street';
SELECT transcript FROM interviews WHERE transcript LIKE '%courthouse%' AND year = 2020 AND month = 7 AND day = 28;
-- The THIEF is:
SELECT DISTINCT name FROM people
WHERE people.phone_number IN (SELECT DISTINCT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60)
INTERSECT
SELECT DISTINCT name FROM people 
WHERE license_plate IN (SELECT DISTINCT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = 'exit')
INTERSECT
SELECT name FROM people WHERE id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN 
        (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = 'Fifer Street' AND transaction_type = 'withdraw'))
INTERSECT  
SELECT people.name FROM people
JOIN passengers ON passengers.flight_id = flights.id
JOIN flights ON flights.id = passengers.flight_id
WHERE passengers.passport_number = people.passport_number AND flight_id = (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN (
    SELECT id FROM airports WHERE city = 'Fiftyville') ORDER BY hour, minute);
-- The ACCOMPLICE is:
SELECT name FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls 
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND
caller = (SELECT phone_number FROM people WHERE name = 'Ernest'));
-- The thief ESCAPED TO:
SELECT city FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
WHERE flights.id = (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id IN (
    SELECT id FROM airports WHERE city = 'Fiftyville') ORDER BY hour, minute);
