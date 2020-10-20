SELECT name
FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE people.name = (SELECT name FROM people WHERE people.name = "Kevin Bacon" AND people.birth = '1958');