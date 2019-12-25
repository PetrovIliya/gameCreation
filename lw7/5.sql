USE rental;

SELECT
	CONCAT_WS(' ', c.first_name, c.last_name) client_name,
	d.title,
	o.offer_date
FROM
	offer o
	INNER JOIN customer c USING(customer_id)
	INNER JOIN dvd d USING(dvd_id)
WHERE
	o.return_date IS NULL;