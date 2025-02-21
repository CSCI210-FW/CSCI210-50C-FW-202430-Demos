-- SQLite
create table PAYMENT(
    payment_id integer primary key,
    payment_date text not null default(date('now')),
    cus_code integer references customer(cus_code) not null,
    payment_amount real not null check(payment_amount > 0))