-- Ronit FIlsele

SELECT DISTINCT a.first_name, a.last_name
FROM actor a
         JOIN cast c ON a.id = c.actor_id
         JOIN movie m ON c.movie_id = m.id
WHERE a.id IN (
    SELECT actor_id
    FROM cast c1
             JOIN movie m1 ON c1.movie_id = m1.id
    WHERE m1.year BETWEEN 1850 AND 1899
)
  AND a.id IN (
    SELECT actor_id
    FROM cast c2
             JOIN movie m2 ON c2.movie_id = m2.id
    WHERE m2.year BETWEEN 1900 AND 1949
);


-- I got anothe one too with union
SELECT DISTINCT a.id, a.first_name, a.last_name, a.gender
FROM actor a
         JOIN "cast" c ON a.id = c.actor_id
         JOIN movie m ON c.movie_id = m.id
where m.year BETWEEN 1850 and 1899

UNION

SELECT DISTINCT a.id, a.first_name, a.last_name, a.gender
FROM actor a
         JOIN "cast" c ON a.id = c.actor_id
         JOIN movie m ON c.movie_id = m.id
where m.year BETWEEN 1900 and 1949