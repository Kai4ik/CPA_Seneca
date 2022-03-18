-- ***********************
-- Purpose: Lab 1 DBS311
-- ***********************

-- Question 1 
/*    Write a query to display the tomorrow�s date in the following format:
      January 10th of year 2019
      the result will depend on the day when you RUN/EXECUTE this query.  
      Label the column �Tomorrow�.
*/

-- Q1 SOLUTION --

define today = sysdate;
SELECT
   TO_CHAR ( &today + 1, 'fmMonth DD"th of year" YYYY') AS "Tomorrow" 
FROM
   DUAL;

-- Question 2 
/*     For each product in category 2, 3, and 5, show product ID, product name, 
       list price, and the new list price increased by 2%. Display a new list 
       price as a whole number. In your result, add a calculated column to show 
       the difference of old and new list prices.
*/

-- Q2 Solution �-

SELECT
   p.product_id,
   p.product_name,
   p.list_price,
   round(((list_price / 100 * 2) + list_price), 0)AS "New list price",
   round(round(((list_price / 100 * 2) + list_price), 0) - p.list_price, 2) AS "Price Difference" 
FROM
   products p 
WHERE
   p.category_id = 2 
   OR p.category_id = 3 
   OR p.category_id = 5 
ORDER BY
   p.category_id,
   p.product_id;

-- Question 3 
/*       For employees whose manager ID is 2, write a query that displays the 
         employee�s Full Name and Job Title in the following format:
         SUMMER, PAYNE is Public Accountant.
*/

-- Q3 Solution �-

SELECT
   concat(concat(concat(concat(concat(e.last_name, ', '), e.first_name), ' is '), e.job_title), '.') AS "FULL name 
   AND POSITION" 
FROM
   employees e 
WHERE
   e.manager_id = 2 
ORDER BY
   e.employee_id;

-- Question 4 --
/*         For each employee hired before October 2016, display the employee�s 
           last name, hire date and calculate the number of YEARS between TODAY 
           and the date the employee was hired.
           * Label the column Years worked. 
           * Order your results by the number of years employed.  
           Round the number of years employed up to the closest whole number.
*/

-- Q4 Solution �-

SELECT
   e.last_name,
   to_char(e.hire_date, 'DD-MON-YY') AS "Hire DATE",
   round((trunc(sysdate) - trunc(e.hire_date)) / 365) AS "Years worked" 
FROM
   employees e 
WHERE
   hire_date < to_date('01-10-16', 'DD-MM-YY') 
ORDER BY
   e.hire_date,
   "Years worked";

-- Question 5 --
/*         
            Display each employee�s last name, hire date, and the review date, which is the first Tuesday after a year of service, but only for those hired after 2016.  
	        * Label the column REVIEW DAY. 
            * Format the dates to appear in the format like:
                TUESDAY, August the Thirty-First of year 2016
            * Sort by review date
*/

-- Q5 Solution �-

SELECT
   e.last_name,
   to_char(e.hire_date, 'DD-MON-YY') AS "Hire Date",
   TO_CHAR(next_day(trunc(add_months(hire_date, 12)), 'TUESDAY'), 'fmDAY, Month "the "ddspth" of year" YYYY') AS "Review Date" 
FROM
   employees e 
WHERE
   hire_date > to_date('01-01-16', 'DD-MM-YY') 
ORDER BY
   next_day(trunc(add_months(hire_date, 12)), 'TUESDAY');

-- Question 6 --
/*         
            For all warehouses, display warehouse id, warehouse name, city, and state. 
            For warehouses with the null value for the state column, display �unknown�.
*/

-- Q6 Solution �-

SELECT
   w.warehouse_id,
   w.warehouse_name,
   l.city,
   nvl2(l.state, l.state, 'Unknown') AS "State" 
FROM
   warehouses w 
   INNER JOIN
      locations l 
      ON w.location_id = l.location_id 
ORDER BY
   w.warehouse_id;