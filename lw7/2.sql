USE rental;

CREATE TABLE IF NOT EXISTS dvd (
  dvd_id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  title VARCHAR(255) NOT NULL,
  production_year INT NOT NULL
) ENGINE = INNODB;

CREATE TABLE IF NOT EXISTS customer (
  customer_id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  first_name  VARCHAR(255) NULL,
  last_name VARCHAR(255) NOT NULL,
  passport_code VARCHAR(11) NOT NULL UNIQUE,
  registration_date TIMESTAMP
) ENGINE = INNODB;

CREATE TABLE IF NOT EXISTS offer (
  offer_id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  dvd_id INT NOT NULL,
  customer_id INT NOT NULL,
  offer_date TIMESTAMP,
  return_date DATETIME
) ENGINE = INNODB;