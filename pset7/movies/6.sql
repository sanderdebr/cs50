SELECT AVG(rating) FROM
ratings JOIN movies ON movies.id = ratings.movie_id
WHERE (SELECT year FROM movies WHERE year = '2012');