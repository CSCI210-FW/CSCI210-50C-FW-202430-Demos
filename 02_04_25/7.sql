select invoice.*,line.*, cus_lname
from INVOICE
    join customer on invoice.cus_code = customer.cus_code
    join line on line.inv_number = invoice.inv_number
    join product on line.p_code = product.p_code
    left join vendor on product.v_code = vendor.v_code