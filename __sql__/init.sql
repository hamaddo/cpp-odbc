/*клиент*/
CREATE TABLE clients
(
    id              serial PRIMARY KEY,
    registry_number numeric      NOT NULL,
    full_name       varchar(255) NOT NULL,
    address         varchar(255) NOT NULL,
    gender          varchar(255) NOT NULL,
    phone           varchar(255) NOT NULL,
);

/*заявки*/
CREATE TABLE requests
(
    id            serial PRIMARY KEY,
    position_name varchar(255) not null,
    address       varchar(255) NOT NULL,
    salary        numeric      not null,
    city_district varchar(255) not null,
    client_id     serial       not null,

    FOREIGN KEY (client_id) REFERENCES clients (id)
);

/*Работодатели*/
CREATE TABLE employers
(
    id                           serial       NOT NULL PRIMARY KEY,
    company_name                 varchar(255) NOT NULL,
    /* организационно правовая форма */
    olf                          varchar(255) NOT NULL,
    ownership_type               varchar(255) not null,
    address                      varchar(255) not null,
    phone                        varchar(255) not null,
    personnel_inspector_fullname varchar(255) not null
);

CREATE TABLE requests_match
/*совпадение заявки клиента и работадателя*/
(
    id          serial primary key,
    request_id  serial not null,
    employer_id serial not null,


    FOREIGN KEY (request_id) REFERENCES requests (id),
    FOREIGN KEY (employer_id) REFERENCES employers (id)
);