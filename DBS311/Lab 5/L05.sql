-- ***********************
-- Purpose: Lab 5 DBS311
-- ***********************

SET SERVEROUTPUT ON; 

-- Question 1 � procedure which checks if given integer is even or odd

-- Q1 SOLUTION �

create or replace procedure even_or_odd (
    numb INT
) AS
BEGIN
    IF (mod(numb,2) = 0) THEN 
        DBMS_OUTPUT.PUT_LINE('EVEN');
    ELSE 
        DBMS_OUTPUT.PUT_LINE('ODD');
    END IF;
    
    EXCEPTION
    WHEN OTHERS
        THEN DBMS_OUTPUT.PUT_LINE('Error!');
END even_or_odd;

-- execution of this procedure with two different parameters - even and odd number

BEGIN
    even_or_odd(5);
    even_or_odd(90);
END;

--------------------------------------------------

-- Question 2 � procedure that finds employee by given ID number and prints information about 
--              this employee 

-- Q2 SOLUTION �

CREATE OR REPLACE PROCEDURE find_employee (
    emp_id NUMBER
) AS
    fname employees.first_name%TYPE;
    lname employees.last_name%TYPE;
    email employees.email%TYPE;
    phone employees.phone%TYPE;
    hire_date employees.hire_date%TYPE;
    job_title employees.job_title%TYPE;
    BEGIN
        SELECT
            employees.first_name,
            employees.last_name,
            employees.email,
            employees.phone,
            employees.hire_date,
            employees.job_title 
            INTO fname,
            lname,
            find_employee.email,
            find_employee.phone,
            find_employee.hire_date,
            find_employee.job_title 
            FROM
               employees 
            WHERE
            employees.employee_id = emp_id;
            DBMS_OUTPUT.PUT_LINE('First name: ' || fname);
            DBMS_OUTPUT.PUT_LINE('Last name: ' || lname);
            DBMS_OUTPUT.PUT_LINE('Email: ' || email);
            DBMS_OUTPUT.PUT_LINE('Phone: ' || phone);
            DBMS_OUTPUT.PUT_LINE('Hire date: ' || hire_date);
            DBMS_OUTPUT.PUT_LINE('Job title: ' || job_title);
            
            EXCEPTION
            WHEN TOO_MANY_ROWS
                THEN DBMS_OUTPUT.PUT_LINE('Too many rows returned! ');
            WHEN OTHERS
                THEN DBMS_OUTPUT.PUT_LINE('Error occured! ');
    END;

-- execution of this procedure which finds employee with ID = 16

BEGIN
    find_employee(16);
END;

--------------------------------------------------

-- I have created copy of products table in order not to change values in original one

create table products_copy as (select * from products); 

-- Question 3 � procedure that increases price of all products in given gategory by given
--              amount

-- Q3 SOLUTION �-

create or replace procedure update_price_by_cat (
    category_id IN products_copy.list_price%TYPE,
    amount NUMBER
) AS
    rows_updated NUMBER;
BEGIN
    UPDATE products_copy
    set products_copy.list_price = products_copy.list_price + amount
    where products_copy.category_id = update_price_by_cat.category_id;
    rows_updated := sql%rowcount;
    if rows_updated > 0 
        THEN DBMS_OUTPUT.PUT_LINE('Rows updated: ' || rows_updated);
    end if;
    EXCEPTION
    WHEN OTHERS
        THEN DBMS_OUTPUT.PUT_LINE('Error!');
END;

-- execution of this procedure where price of all products in category 2 should be
--increased on $10

BEGIN
    update_price_by_cat(2,10);
END;

--------------------------------------------------

-- Question 4 � procedure that increases the price of products whose price is less than
--              the average price of all products by 1% or 2% depending on ratio of price
--              to average.

-- Q4 SOLUTION �-

create or replace procedure update_price_under_avg AS
    average float;
    rows_updated NUMBER;
BEGIN
    select round(avg(products_copy.list_price),2) into average from products_copy;
    if average <= 1000 THEN
            UPDATE products_copy
            SET products_copy.list_price = products_copy.list_price * 1.01
            where products_copy.list_price < average;
    elsif average > 1000 THEN
            UPDATE products_copy
            SET products_copy.list_price = products_copy.list_price * 1.02
            where products_copy.list_price < average;       
    end if;
    
    rows_updated := sql%rowcount;
    
    DBMS_OUTPUT.PUT_LINE('Average: ' || average);
    DBMS_OUTPUT.PUT_LINE('Rows updated: ' || rows_updated);
    
    EXCEPTION
    WHEN VALUE_ERROR 
        THEN DBMS_OUTPUT.PUT_LINE('Value error occured! ');
    WHEN OTHERS
        THEN DBMS_OUTPUT.PUT_LINE('Error occured! ');
END;


-- execution of this procedure 

BEGIN
    update_price_under_avg();
END;

--------------------------------------------------

-- Question 5 � procedure that shows report of products based on their prices.
--              There are 3 categories - cheap, fair, expensive

-- Q5 SOLUTION �-

create or replace procedure report AS
    min_p NUMBER(9,2);
    max_p NUMBER (9,2);
    avrg NUMBER (9,2);
    c_amount INT;
    f_amount INT;
    e_amount INT;
BEGIN
    select avg(products_copy.list_price) into avrg from products_copy;
    select min(products_copy.list_price) into min_p from products_copy;
    select max(products_copy.list_price) into max_p from products_copy;
    
    select count(products_copy.product_id) into c_amount from products_copy 
    where products_copy.list_price < (avrg-min_p)/2;
    
    select count(products_copy.product_id) into e_amount from products_copy 
    where products_copy.list_price > (max_p - avrg)/2;
    
    select count(products_copy.product_id) into f_amount from products_copy 
    where products_copy.list_price between (avrg-min_p)/2 and (max_p - avrg)/2;
    
    DBMS_OUTPUT.PUT_LINE('Cheap: ' || c_amount);
    DBMS_OUTPUT.PUT_LINE('Fair: ' || f_amount);
    DBMS_OUTPUT.PUT_LINE('Expensive: ' || e_amount);
    
    EXCEPTION
    WHEN ZERO_DIVIDE
        THEN DBMS_OUTPUT.PUT_LINE('Zero division prohibited! ');
    WHEN OTHERS
        THEN DBMS_OUTPUT.PUT_LINE('Error occured! ');
END;

-- execution of this procedure 

BEGIN
    report();
END;