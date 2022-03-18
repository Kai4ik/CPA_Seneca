-- ***********************
-- Purpose: Lab 4 DBS311
-- ***********************

-- Question 1 --
/*   Display cities that no warehouse is located in them. 
    (use set operators to answer this question)
*/

-- Q1 SOLUTION --

SELECT
   loc.city 
FROM
   warehouses ware 
   RIGHT JOIN
      locations loc 
      ON loc.location_id = ware.location_id 
MINUS
SELECT
    loc.city 
FROM
    warehouses ware 
    INNER JOIN
        locations loc 
        ON loc.location_id = ware.location_id 
    ORDER BY 1;
      
-- Question 2 --
/*   Display the category ID, category name, and the number of products 
     in category 1, 2, and 5. In your result, display first the number 
     of products in category 5, then category 1 and then 2.
*/

-- Q2 SOLUTION -- 

SELECT
   cat.category_id,
   cat.category_name,
   COUNT(prod.product_id) AS "Number of products" 
FROM
   product_categories cat 
   INNER JOIN
      products prod 
      ON prod.category_id = cat.category_id 
WHERE
   cat.category_id = 5 
GROUP BY
   cat.category_id,
   cat.category_name 
UNION ALL
SELECT
   cat.category_id,
   cat.category_name,
   COUNT(prod.product_id) AS "Number of products"
FROM
   product_categories cat 
   INNER JOIN
      products prod 
      ON prod.category_id = cat.category_id 
WHERE
   cat.category_id = 1 
GROUP BY
   cat.category_id,
   cat.category_name 
UNION ALL
SELECT
   cat.category_id,
   cat.category_name,
   COUNT(prod.product_id) AS "Number of products" 
FROM
   product_categories cat 
   INNER JOIN
      products prod 
      ON prod.category_id = cat.category_id 
WHERE
   cat.category_id = 2 
GROUP BY
   cat.category_id,
   cat.category_name;

-- Question 3 --
/*   Display product ID for products whose quantity in the 
     inventory is less than to 5. (You are not allowed to 
     use JOIN for this question.)
*/

-- Q3 SOLUTION -- 

SELECT
   ord.product_id 
FROM
   order_items ord 
INTERSECT
SELECT
   inv.product_id 
FROM
   inventories inv 
WHERE
   inv.quantity < 5;
   
   -- Question 4 --
/*   We need a single report to display all warehouses and the 
     state that they are located in and all states regardless 
     of whether they have warehouses in them or not. (Use set
     operators in you answer.)
*/

-- Q4 SOLUTION -- 

SELECT
   ware.warehouse_name,
   loc.state 
FROM
   warehouses ware 
   LEFT JOIN
      locations loc 
      ON loc.location_id = ware.location_id 
   UNION
   SELECT
      ware.warehouse_name,
      loc.state 
   FROM
      warehouses ware 
      FULL JOIN
         locations loc 
         ON loc.location_id = ware.location_id;