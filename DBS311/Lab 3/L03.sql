-- ***********************
-- Purpose: Lab 3 DBS311
-- ***********************

-- Question 1 --
/*   Write a SQL query to display the last name and hire date of 
     all employees who were hired before the
     employee with ID 107 got hired but after March 2016. Sort 
     the result by the hire date and then
     employee ID.
*/

-- Q1 SOLUTION --

SELECT
   emp.last_name,
   to_char(emp.hire_date, 'DD-MON-YY') as "HIRE_DATE"
FROM
   employees emp 
WHERE
   emp.hire_date > TO_DATE('01-04-16', 'DD-MM-YY') 
   AND emp.hire_date < (
   SELECT
      emp.hire_date 
   FROM
      employees emp 
   WHERE
      emp.employee_id = 107) 
   ORDER BY
      emp.hire_date,
      emp.employee_id;
      
-- Question 2 --
/*   Write a SQL query to display customer name and credit limit 
     for customers with lowest credit limit. Sort
     the result by customer ID.
*/

-- Q2 SOLUTION --      

SELECT
   cust.name,
   cust.credit_limit 
FROM
   customers cust 
WHERE
   cust.credit_limit = 
   (
      SELECT
         MIN(cus.credit_limit) 
      FROM
         customers cus
   )
ORDER BY
   cust.customer_id;
   
-- Question 3 --
/*   Write a SQL query to display the product ID, product name, 
     and list price of the highest paid product(s)
     in each category. Sort by category ID and the product ID.
*/

-- Q3 SOLUTION --    

SELECT
   prod.category_id,
   prod.product_id,
   prod.product_name,
   prod.list_price 
FROM
   products prod 
WHERE
   prod.list_price = ANY (
   SELECT
      MAX(prod.list_price) 
   FROM
      products prod 
   GROUP BY
      prod.category_id) 
   ORDER BY
      prod.category_id,
      prod.product_id;
      
-- Question 4 --
/*   Write a SQL query to display the category ID and the category 
    name of the most expensive (highest list price) product(s).
*/

-- Q4 SOLUTION --

SELECT
   prod.category_id,
   pcat.category_name 
FROM
   products prod 
   INNER JOIN
      product_categories pcat 
      ON prod.category_id = pcat.category_id 
WHERE
   prod.list_price = 
   (
      SELECT
         MAX(prod.list_price) 
      FROM
         products prod
   );
   
-- Question 5 --
/*   Write a SQL query to display product name and list price 
     for products in category 1 which have the list
     price less than the lowest list price in ANY category. 
     Sort the output by top list prices first and then by
     the product ID.
*/

-- Q5 SOLUTION --   

SELECT
   prod.product_name,
   prod.list_price 
FROM
   products prod 
WHERE
   prod.category_id = 1 
   AND prod.list_price < ANY (
   SELECT
      MIN(prod.list_price) 
   FROM
      products prod 
   GROUP BY
      prod.category_id) 
   ORDER BY
      prod.list_price DESC,
      prod.product_id;
      
-- Question 6 --
/*   Display the maximum price (list price) 
     of the category(s) that has the lowest price product.
*/

-- Q6 SOLUTION -- 

SELECT
   MAX(prod.list_price) AS "Maximum Price" 
FROM
   products prod 
WHERE
   prod.category_id = 
   (
      SELECT
         prod.category_id 
      FROM
         products prod 
      WHERE
         prod.list_price = 
         (
            SELECT
               MIN(prod.list_price) 
            FROM
               products prod
         )
    );