Select actor.act_id, actor.act_year, actor.act_fname, actor.act_lname 
from ACTOR, MOVIE
where
Movie_year >= 1850 and Movie_year <= 1950
