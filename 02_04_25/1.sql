select a.* 
from cast c
    join actor a
        on a.id = c.actor_id
    join movie m
        on m.id = c.movie_id    
where m.year >= 1850 
    and m.year <= 1900
    and exists (
        select null
        from cast c2
            join actor a2 on a2.id = c2.actor_id
            join movie m2 on m2.id = c2.movie_id
        where m2.year >= 1900
            and m2.year <= 1950
            and a2.id = a.id
    )


--I was also considering using IN statments in place of '= any()'
--select * 
--from actor a
--where 
--    a.id = any(
--        select actor_id from cast c
--            join movie m on m.id = c.id
--        where m.year >= 1850
--            and m.year < 1900
--    ) 
--    and a.id = any(
--        select actor_id from cast c
--            join movie m on m.id = c.id
--        where m.year >= 1900
--            and m.year <= 1950
--    )