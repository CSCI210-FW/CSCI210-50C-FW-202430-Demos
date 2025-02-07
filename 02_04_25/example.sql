-- SQLite
SELECT invoice.inv_number, inv_date, count(*) as 'Number of Lines',
    sum(line_units * line_price) as 'Invoice Total', p_code
from INVOICE 
    join line on invoice.inv_number = line.inv_number
group by invoice.inv_number
having sum(line_units * line_price) > 100

