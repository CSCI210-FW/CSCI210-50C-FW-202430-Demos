-- SQLite
create table line(
    inv_number integer references invoice(inv_number),
    line_number integer,
    p_code text references product(p_code),
    line_units integer not null,
    line_price real not null,
    primary key (inv_number, line_number)
    ) strict