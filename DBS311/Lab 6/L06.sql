-- ***********************
-- Purpose: Lab 6 DBS311
-- ***********************

SET SERVEROUTPUT ON;

-- Question 1 � procedure that gets an integer number and calculates and displays its factorial.

-- Q1 SOLUTION �-
-- First version by using basic loop 

-- Solution 1.1

CREATE OR replace PROCEDURE factorial (numb INT) AS 
    factor INT := 1;
    iter INT := 1;
BEGIN
        LOOP 
            factor := factor * iter;
            iter := iter + 1;
            EXIT WHEN iter > numb;
        END LOOP;
    DBMS_OUTPUT.PUT_LINE('!' || numb || ' = ' || factor);
    EXCEPTION 
        WHEN VALUE_ERROR 
            THEN DBMS_OUTPUT.PUT_LINE('Value Error Occured!');
        WHEN OTHERS 
            THEN DBMS_OUTPUT.PUT_LINE('Error!');
END factorial;

--------------------------------------------------

-- New version by using for loop (07.27.20). We do not need to include exit statement, make iteration and respectively declare variable for iteration

-- Solution 1.2

CREATE OR replace PROCEDURE factorial_new (numb INT) AS 
    factor INT := 1;
BEGIN
        FOR iter IN 1..numb LOOP 
            factor := factor * iter;
        END LOOP;
    DBMS_OUTPUT.PUT_LINE('!' || numb || ' = ' || factor || '(new)');
    EXCEPTION 
        WHEN VALUE_ERROR 
            THEN DBMS_OUTPUT.PUT_LINE('Value Error Occured!');
        WHEN OTHERS 
            THEN DBMS_OUTPUT.PUT_LINE('Error!');
END factorial_new;

-- execution of this procedure 

begin
    factorial(5);
    factorial_new(6);
end;

--------------------------------------------------

-- Question 2 � procedure that gets an employee number and calculates his salary.

-- Q2 SOLUTION �

-- First version by using basic loop 

-- Solution 1.1

CREATE OR REPLACE PROCEDURE calculate_salary (emp_id employees.employee_id%TYPE) AS
    years_worked NUMBER := 0;
    iterator NUMBER := 0;
    salary DECIMAL(8,2) := 10000;
    emp_fname employees.first_name%TYPE;
    emp_lname employees.last_name%TYPE;
BEGIN
    DBMS_OUTPUT.PUT_LINE('  Salary Report  ');
    DBMS_OUTPUT.PUT_LINE('---------------------------------');
    SELECT RPAD(employees.first_name, 25, ' '), RPAD(employees.last_name, 25, ' '),extract(year from sysdate)-extract(year from hire_date) INTO emp_fname, emp_lname, years_worked FROM employees WHERE employees.employee_id = emp_id;
    LOOP
        salary := salary + (salary/100 * 5);
        iterator := iterator + 1;
        EXIT WHEN iterator >= years_worked;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Employee First Name: ' || emp_fname);
    DBMS_OUTPUT.PUT_LINE('Employee Last Name: ' || emp_lname);
    DBMS_OUTPUT.PUT_LINE('Employee Salary: ' || salary);
    EXCEPTION
        WHEN TOO_MANY_ROWS
            THEN DBMS_OUTPUT.PUT_LINE('Too many rows were returned! ');
        WHEN NO_DATA_FOUND
            THEN DBMS_OUTPUT.PUT_LINE('Employee with such ID not found! ');
        WHEN OTHERS 
            THEN DBMS_OUTPUT.PUT_LINE('Error occured!');
END calculate_salary;

--------------------------------------------------

-- New version by using while loop (07.27.20). We do not need to include exit statement because its already mentioned in condtition to while loop

-- Solution 1.2

CREATE OR REPLACE PROCEDURE calculate_salary_new (emp_id employees.employee_id%TYPE) AS
    years_worked NUMBER := 0;
    iterator NUMBER := 0;
    salary DECIMAL(8,2) := 10000;
    emp_fname employees.first_name%TYPE;
    emp_lname employees.last_name%TYPE;
BEGIN
    DBMS_OUTPUT.PUT_LINE('  Salary Report  ');
    DBMS_OUTPUT.PUT_LINE('---------------------------------');
    SELECT RPAD(employees.first_name, 25, ' '), RPAD(employees.last_name, 25, ' '),extract(year from sysdate)-extract(year from hire_date) INTO emp_fname, emp_lname, years_worked FROM employees WHERE employees.employee_id = emp_id;
    WHILE iterator < years_worked LOOP
        salary := salary + (salary/100 * 5);
        iterator := iterator + 1;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Employee First Name: ' || emp_fname);
    DBMS_OUTPUT.PUT_LINE('Employee Last Name: ' || emp_lname);
    DBMS_OUTPUT.PUT_LINE('Employee Salary: ' || salary);
    EXCEPTION
        WHEN TOO_MANY_ROWS
            THEN DBMS_OUTPUT.PUT_LINE('Too many rows were returned! ');
        WHEN NO_DATA_FOUND
            THEN DBMS_OUTPUT.PUT_LINE('Employee with such ID not found! ');
        WHEN OTHERS 
            THEN DBMS_OUTPUT.PUT_LINE('Error occured!');
END calculate_salary_new;

-- execution of this procedure 

BEGIN 
    calculate_salary(66);
    DBMS_OUTPUT.PUT_LINE('---------------------------------');
    calculate_salary_new(65);
END;

--------------------------------------------------

-- Question 3 � procedure that prints warehouses report

-- Q3 SOLUTION �

-- First version by using basic loop 

-- Solution 1.1

CREATE  OR REPLACE PROCEDURE warehouses_report AS 
    ware_id warehouses.warehouse_id % TYPE := 1;
    ware_name warehouses.warehouse_name %TYPE;
    city locations.city %TYPE;
    state locations.state %TYPE;
BEGIN
        DBMS_OUTPUT.PUT_LINE('  Warehouses Report  ');
        DBMS_OUTPUT.PUT_LINE('---------------------------------');
    LOOP 
        SELECT warehouses.warehouse_id, RPAD(warehouses.warehouse_name, 25, ' '), RPAD(locations.city, 25, ' '), RPAD(nvl(locations.state, 'no state'), 25, ' ') 
        INTO ware_id, ware_name, warehouses_report.city, warehouses_report.state FROM warehouses INNER JOIN locations ON locations.location_id = warehouses.location_id WHERE warehouse_id = ware_id;
        DBMS_OUTPUT.PUT_LINE('Warehouse ID:  ' || ware_id);
        DBMS_OUTPUT.PUT_LINE('Warehouse Name:  ' || ware_name);
        DBMS_OUTPUT.PUT_LINE('City: ' || city);
        DBMS_OUTPUT.PUT_LINE('State: ' || state);
        DBMS_OUTPUT.PUT_LINE('---------------------------------');
        ware_id := ware_id + 1;
        EXIT WHEN ware_id > 9;
    END LOOP;
    EXCEPTION
        WHEN NO_DATA_FOUND
            THEN DBMS_OUTPUT.PUT_LINE('Warehouse with such ID not found! ');
        WHEN TOO_MANY_ROWS
            THEN DBMS_OUTPUT.PUT_LINE('Too many rows were returned! ');
        WHEN OTHERS 
            THEN DBMS_OUTPUT.PUT_LINE('Error occured!');
END warehouses_report;

-- execution of this procedure 

BEGIN 
    warehouses_report();
END;

--------------------------------------------------

-- New version by using cursor for loop (07.27.20). I have declared cursor in declaration section which is equal to table with all warehouses and their locations (city,state).
--                                                  And then by using for loop we fetch each row from cursor and display it's info. Like in first task, we don't need iterator, exit condition.

-- Solution 1.2

CREATE  OR REPLACE PROCEDURE warehouses_report_new AS 
    CURSOR warehouses_list IS SELECT warehouses.warehouse_id, RPAD(warehouses.warehouse_name, 25, ' ') AS ware_name, RPAD(locations.city, 25, ' ') AS city, RPAD(nvl(locations.state, 'no state'), 25, ' ') AS state  
    FROM warehouses INNER JOIN locations ON locations.location_id = warehouses.location_id ORDER BY warehouses.warehouse_id;
BEGIN
        DBMS_OUTPUT.PUT_LINE('  Warehouses Report  ');
        DBMS_OUTPUT.PUT_LINE('---------------------------------');
        FOR elem IN warehouses_list LOOP 
        DBMS_OUTPUT.PUT_LINE('Warehouse ID:  ' || elem.warehouse_id);
        DBMS_OUTPUT.PUT_LINE('Warehouse Name:  ' || elem.ware_name);
        DBMS_OUTPUT.PUT_LINE('City: ' || elem.city);
        DBMS_OUTPUT.PUT_LINE('State: ' || elem.state);
        DBMS_OUTPUT.PUT_LINE('---------------------------------');
    END LOOP;
    EXCEPTION
        WHEN NO_DATA_FOUND
            THEN DBMS_OUTPUT.PUT_LINE('Warehouse with such ID not found! ');
        WHEN TOO_MANY_ROWS
            THEN DBMS_OUTPUT.PUT_LINE('Too many rows were returned! ');
        WHEN OTHERS 
            THEN DBMS_OUTPUT.PUT_LINE('Error occured!');
END warehouses_report_new;

-- execution of this procedure 

BEGIN 
    warehouses_report_new();
END;
