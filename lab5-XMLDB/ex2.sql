--XML storage
--create table printers
CREATE TABLE printers (id BIGSERIAL PRIMARY KEY, name varchar(50) NOT NULL, description XML);
