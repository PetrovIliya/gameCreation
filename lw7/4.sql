USE rental;

SELECT
	d.title
FROM
	dvd d
WHERE
	d.production_year = 2010
ORDER BY 
	d.title;