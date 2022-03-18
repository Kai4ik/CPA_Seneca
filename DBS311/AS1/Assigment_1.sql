-- Q1 --

/* Display the employee number, full employee name, job title, and hire date of all
employees hired in September with the most recently hired employees displayed
first. */

-- Q1 Solution --

SELECT
   emp.employee_id AS "Employee Number",
   concat(concat(concat(emp.last_name, ','), ' '), emp.first_name) AS "Full Name",
   emp.job_title AS "Job Title",
   TO_CHAR(emp.hire_date, 'fm"["Month DD"th of" YYYY"]"') AS "Start Date" 
FROM
   employees emp 
WHERE
   EXTRACT(MONTH FROM emp.hire_date) = 9 
ORDER BY
   emp.hire_date DESC;

-- Q2 --

/* The company wants to see the total sale amount per sales person (salesman) for all
orders. Assume that online orders do not have any sales representative. For online
orders (orders with no salesman ID), consider the salesman ID as 0. Display the
salesman ID and the total sale amount for each employee.
Sort the result according to employee number */

-- Q2 Solution --

SELECT
   nvl2(emp.employee_id, emp.employee_id, 0) AS "Employee Number",
   to_char (SUM(oi.quantity*oi.unit_price), '$999,999,999.99') AS "Total Sale"
FROM
   employees emp 
   RIGHT JOIN
      orders ord 
      ON ord.salesman_id = emp.employee_id 
   LEFT JOIN
      order_items oi 
      ON ord.order_id = oi.order_id 
GROUP BY
   emp.employee_id 
ORDER BY
   nvl(emp.employee_id, 0);

-- Q3 --

/* Display customer Id, customer name and total number of orders for customers that
the value of their customer ID is in values from 35 to 45. Include the customers with
no orders in your report if their customer ID falls in the range 35 and 45.
Sort the result by the value of total orders. */

-- Q3 Solution --

SELECT
   cust.customer_id,
   cust.name,
   COUNT(ord.order_id) AS "Total Orders" 
FROM
   customers cust 
   LEFT JOIN
      orders ord 
      ON ord.customer_id = cust.customer_id 
WHERE
   cust.customer_id >= 35 
   AND cust.customer_id <= 45 
GROUP BY
   cust.customer_id,
   cust.name 
ORDER BY
   "Total Orders";
   
-- Q4 --

/*  Display customer ID, customer name, and the order ID and the order date of all
orders for customer whose ID is 44.
a. Show also the total quantity and the total amount of each customer’s order.
b. Sort the result from the highest to lowest total order amount. */

-- Q4 Solution --

SELECT
   cus.customer_id,
   cus.name,
   ord.order_id,
   to_char(ord.order_date, 'DD-MON-YY') AS "Order date",
   SUM(oitem.quantity) AS "Total Items",
   to_char(SUM(oitem.quantity*oitem.unit_price), '$999,999,999.99') AS "Total Amount" 
FROM
   customers cus 
   INNER JOIN
      orders ord 
      ON cus.customer_id = ord.customer_id 
   INNER JOIN
      order_items oitem 
      ON ord.order_id = oitem.order_id 
WHERE
   cus.customer_id = 44 
GROUP BY
   cus.customer_id,
   cus.name,
   ord.order_id,
   ord.order_date 
ORDER BY
   "Total Amount" DESC;

-- Q5 --

/*  Display customer Id, name, total number of orders, the total number of items
ordered, and the total order amount for customers who have more than 30 orders.
Sort the result based on the total number of orders. */

-- Q5 Solution --

SELECT
   cust.customer_id,
   cust.name,
   COUNT(oitem.order_id) AS "Total Number Of Orders",
   SUM(oitem.quantity) AS "Total Items",
   to_char(SUM(oitem.quantity*oitem.unit_price), '$999,999,999.99') AS "Total Amount" 
FROM
   customers cust 
   INNER JOIN
      orders ord 
      ON ord.customer_id = cust.customer_id 
   INNER JOIN
      order_items oitem 
      ON ord.order_id = oitem.order_id 
HAVING
    COUNT(oitem.order_id) > 30 
GROUP BY
   cust.customer_id,
   cust.name 
ORDER BY
   "Total Number Of Orders";

-- Q6 --

/*  Display Warehouse Id, warehouse name, product category Id, product category
name, and the lowest product standard cost for this combination.
• In your result, include the rows that the lowest standard cost is less then $200.
• Also, include the rows that the lowest cost is more than $500.
• Sort the output according to Warehouse Id, warehouse name and then product
category Id, and product category name. */

-- Q6 Solution --

SELECT
   w.warehouse_id AS "Warehouse ID",
   w.warehouse_name AS "Warehouse Name",
   p.category_id AS "Category ID",
   pc.category_name AS "Category Name",
   TO_CHAR(MIN(p.standard_cost), '$999.99') AS "Lowest Cost" 
FROM
   warehouses w 
   INNER JOIN
      inventories i 
      ON w.warehouse_id = i.warehouse_id 
   INNER JOIN
      products p 
      ON p.product_id = i.product_id 
   INNER JOIN
      product_categories pc 
      ON pc.category_id = p.category_id 
GROUP BY
   w.warehouse_id,
   w.warehouse_name,
   p.category_id,
   pc.category_name 
HAVING
   MIN(p.standard_cost) < 200 
   OR MIN(p.standard_cost) > 500 
ORDER BY
   w.warehouse_id,
   w.warehouse_name,
   p.category_id,
   pc.category_name;

-- Q7 --

/*  Display the total number of orders per month. Sort the result from January to
December. */

-- Q7 Solution --

SELECT
   initcap(to_char(ord.order_date, 'MONTH')) AS "Month",
   COUNT(ord.order_id) AS "Number Of orders" 
FROM
   orders ord 
GROUP BY
   EXTRACT(MONTH 
FROM
   ord.order_date),
   to_char(ord.order_date, 'MONTH') 
ORDER BY
   EXTRACT(MONTH 
FROM
   ord.order_date);

-- Q8 --

/*  Display product Id, product name for products that their list price is more than any
highest product standard cost per warehouse outside Americas regions.
(You need to find the highest standard cost for each warehouse that is located
outside the Americas regions. Then you need to return all products that their list
price is higher than any highest standard cost of those warehouses.)
Sort the result according to list price from highest value to the lowest. */

-- Q8 Solution --

SELECT
   pr.product_id,
   pr.product_name,
   to_char(pr.list_price, '$999,999.99') 
FROM
   products pr 
WHERE
   pr.list_price > ANY (
   SELECT
      MAX(pr.standard_cost) 
   FROM
      products pr 
      INNER JOIN
         inventories inv 
         ON inv.product_id = pr.product_id 
      INNER JOIN
         warehouses ware 
         ON ware.warehouse_id = inv.warehouse_id 
      INNER JOIN
         locations loc 
         ON loc.location_id = ware.location_id 
   WHERE
      loc.country_id NOT LIKE '%US%' 
   GROUP BY
      ware.warehouse_id);

-- Q9 --

/*  Write a SQL statement to display the most expensive and the cheapest product (list
price). Display product ID, product name, and the list price. */

-- Q9 Solution --

SELECT
   prod.product_id,
   prod.product_name,
   to_char(prod.list_price, '$999,999,999.99')
FROM
   products prod 
WHERE
   prod.list_price = 
   (
      SELECT
         MAX(prod.list_price) 
      FROM
         products prod
   )
UNION ALL
SELECT
   prod.product_id,
   prod.product_name,
   to_char(prod.list_price, '$999,999,999.99') 
FROM
   products prod 
WHERE
   prod.list_price = 
   (
      SELECT
         MIN(prod.list_price) 
      FROM
         products prod
   );

-- Q10 --

/*  Write a SQL query to display the number of customers with total order amount over
the average amount of all orders, the number of customers with total order amount
under the average amount of all orders, number of customers with no orders, and
the total number of customers.
See the format of the following result. */

-- Q10 Solution --

SELECT
   'Number of customers with total purchase amount over average: ' || COUNT(*) 
FROM
   (
      SELECT
         o.customer_id,
         SUM(quantity * unit_price) 
      FROM
         order_items oi 
         INNER JOIN
            orders o 
            ON o.order_id = oi.order_id 
      GROUP BY
         o.customer_id 
      HAVING
         SUM(quantity * unit_price) > (
         SELECT
            AVG(quantity * unit_price) 
         FROM
            ORDER_ITEMS)
   )
UNION ALL
SELECT
   'Number of customers with total purchase amount below average: ' || COUNT(*) 
FROM
   (
      SELECT
         o.customer_id,
         SUM(quantity * unit_price) 
      FROM
         order_items oi 
         INNER JOIN
            orders o 
            ON o.order_id = oi.order_id 
      GROUP BY
         o.customer_id 
      HAVING
         SUM(quantity * unit_price) < (
         SELECT
            AVG(quantity * unit_price) 
         FROM
            ORDER_ITEMS)
   )
UNION ALL
SELECT
   'Number of customers with no orders: ' || COUNT(*) 
FROM
   customers c 
   LEFT OUTER JOIN
      orders o 
      ON c.customer_id = o.customer_id 
WHERE
   o.order_id is null 
UNION ALL
SELECT
   'Total number of customers: ' || COUNT(*) 
FROM
   customers;
