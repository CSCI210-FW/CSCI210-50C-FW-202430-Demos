-- SQLite
select Emp_FName,
    Emp_LName,
    EMP_HIREDATE
from EMPLOYEE
where job_code = 510
    and emp_hiredate >= date('now', '-16 years');