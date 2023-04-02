SELECT DISTINCT people.name AS n FROM people
JOIN stars
ON people.id = stars.person_id
WHERE people.name != 'Kevin Bacon'
AND movie_id IN (
SELECT movie_id from people
JOIN stars
on stars.person_id = people.id
WHERE name = 'Kevin Bacon' AND birth = '1958');