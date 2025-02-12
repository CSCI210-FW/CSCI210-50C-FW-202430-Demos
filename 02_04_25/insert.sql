-- SQLite
--insert into customer values (NULL, 'Potter', 'Harry', NULL, '615', '555-1212', NULL)
--Note after class. This syntax works just not with the sqlite extension in VS Code. It shoudl work in CodeGrade if you add multiple rows this way.
insert into customer (cus_lname, cus_fname, cus_phone) 
values ('Pitt', 'Brad', '555-2322'), 
('Claus', 'Santa', '222-1212')