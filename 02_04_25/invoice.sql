-- SQLite
create table invoice (
    inv_number integer primary key,
    cus_code integer not null references customer(cus_code),
    inv_date text not null default(date('now'))) strict