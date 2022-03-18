-- ***********************
-- Purpose: Lab 02 DBS311
-- ***********************

-- Question 1 
/*    For each job title display the number 
      of employees. Sort the result according to the number of employees.
*/

-- Q1 SOLUTION --

SELECT
   e.job_title,
   COUNT(e.job_title) AS "EMPLOYEES" 
FROM
   employees e 
GROUP BY
   e.job_title
ORDER BY
   COUNT(e.job_title);

-- Question 2
/*  Display the highest, lowest, and average customer credit limits. Name these 
    results high, low, and average. Add a column that shows the difference 
    between the highest and the lowest credit limits named 
    �High and Low Difference�. Round the average to 2 decimal places.
*/

-- Q2 SOLUTION --

SELECT
   MAX(cust.credit_limit) AS "HIGH",
   MIN(cust.credit_limit) AS "LOW",
   round(AVG(cust.credit_limit), 2) AS "AVERAGE",
   MAX(cust.credit_limit) - MIN(cust.credit_limit) AS "High and Low Difference" 
FROM
   customers cust;

-- Question 3
/*  Display the order id, the total number of products, and the total 
    order amount for orders with the total amount over  $1,000,000. 
    Sort the result based on total amount from the high to low values.
*/

-- Q3 SOLUTION --

SELECT
   orit.order_id,
   SUM(orit.quantity)AS "TOTAL_ITEMS",
   SUM((orit.unit_price*orit.quantity)) AS "TOTAL_AMOUNT" 
FROM
   order_items orit 
GROUP BY
   orit.order_id 
HAVING
   SUM((orit.unit_price*orit.quantity)) > 1000000 
ORDER BY
   "TOTAL_AMOUNT" DESC;

-- Question 4
/*  Display the warehouse id, warehouse name, and the total number 
    of products for each warehouse. Sort the result according to the
    warehouse ID.
*/

-- Q4 SOLUTION --

SELECT
   ware.warehouse_id,
   ware.warehouse_name,
   SUM(inv.quantity) AS "TOTAL_PRODUCTS" 
FROM
   warehouses ware 
   INNER JOIN
      inventories inv 
      ON ware.warehouse_id = inv.warehouse_id 
GROUP BY
   ware.warehouse_id,
   ware.warehouse_name 
ORDER BY
   ware.warehouse_id;

-- Question 5
/*  For each customer display customer number, customer full name, and 
    the total number of orders issued by the customer.
    ? If the customer does not have any orders, the result shows 0.
    ? Display only customers whose customer name starts with �O� and contains �e�.
    ? Include also customers whose customer name ends with �t�.
    ? Show the customers with highest number of orders first.
*/

-- Q5 SOLUTION --

SELECT
   cust.customer_id,
   cust.name,
   COUNT(ord.order_id) AS "Total number of orders"
FROM
   customers cust 
   LEFT JOIN
      orders ord 
      ON ord.customer_id = cust.customer_id 
WHERE
   cust.name LIKE '%t' 
   OR cust.name LIKE 'O%e%' 
GROUP BY
   cust.customer_id,
   cust.name 
ORDER BY
   COUNT(ord.order_id) DESC;
   
-- Question 6
/*  Write a SQL query to show the total and the 
    average sale amount for each category. Round the 
    average to 2 decimal places..
*/

-- Q6 SOLUTION --

SELECT
   pc.category_id,
   SUM(oi.quantity*oi.unit_price) AS "TOTAL_AMOUNT" ,
   round(AVG(oi.quantity*oi.unit_price), 2) AS "AVERAGE_AMOUNT" 
FROM
   product_categories pc 
   INNER JOIN
      products p 
      ON pc.category_id = p.category_id 
   INNER JOIN
      order_items oi 
      ON p.product_id = oi.product_id 
GROUP BY
   p.category_id;