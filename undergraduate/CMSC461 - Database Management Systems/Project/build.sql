create table Newspaper
   (newspaper_name 	varchar(32)	not null unique,
    tele		char(10)	not null,
    addr           	varchar(100)	not null,
    fax            	char(10)	not null,
    contact        	char(32)	not null,
    primary key (newspaper_name));

create table Branch
   (branch_num		int		not null unique, 
    manager        	varchar(32)	not null unique,
    addr_str       	varchar(32)	not null,
    addr_city      	varchar(32)	not null,
    addr_st        	varchar(16)	not null,
    addr_zip       	char(5)		not null,
    fax            	char(10)	not null,
    tele           	char(10)	not null,
    monthly_bonus	int		not null,
    manager_start	date		not null,
    primary key (branch_num),
    check (monthly_bonus >= 0));

create table Client
   (client_num     	int		not null unique,
    name           	varchar(32) 	not null,
    preference     	varchar(32) 	not null,
    max_rent       	int 		not null,
    employee_name  	varchar(32)	not null,
    date_joined    	date 		not null,
    branch_joined  	int,
    primary key (client_num),
    foreign key (branch_joined) references Branch(branch_num)
				on delete set null);

create table ClientHomeTele
   (client_num     	int		not null,
    home_tele      	char(10) 	not null,
    primary key (client_num, home_tele),
    foreign key (client_num) references Client);

create table ClientWorkTele
   (client_num     	int 		not null,
    work_tele      	char(10) 	not null,
    primary key (client_num, work_tele),
    foreign key (client_num) references Client);

create table Employee
   (emp_num        	int 		not null unique,
    position       	char(15) 	not null,
    branch_num     	int 		not null,
    supervisor		varchar(32),
    name           	varchar(64) 	not null,
    salary         	float(2) 	not null,
    addr           	varchar(100) 	not null,
    sex            	char(1) 	not null,
    dob            	date 		not null,
    primary key (emp_num),
    check (position in ('Associate','Supervisor')),
    check (salary >= 0),
    foreign key (branch_num) references Branch);

create table PropOwner
   (name           	varchar(64) 	not null unique,
    private		char(3)		not null,
    addr           	varchar(100) 	not null,
    contact        	varchar(32),
    type           	varchar(64),
    primary key (name));

create table PropOwnerTele
   (name           	varchar(64) 	not null,
    tele           	char(10) 	not null,
    primary key (name),
    foreign key (name) references PropOwner);

create table PropOwnerFax
   (name           	varchar(64) 	not null,
    fax            	char(10) 	not null,
    primary key (name),
    foreign key (name) references PropOwner);

create table Property
   (property_num   	int 		not null unique,
    owner          	varchar(32) 	not null,
    rent           	float(2) 	not null,
    fee            	float(2) 	not null,
    bedrooms       	smallint 	not null,
    bathrooms      	smallint 	not null,
    sq_footage     	int 		not null,
    type           	varchar(32) 	not null,
    addr_str       	varchar(32) 	not null,
    addr_city      	varchar(32) 	not null,
    addr_st        	varchar(16) 	not null,
    addr_zip       	char(5) 	not null,
    primary key (property_num),
    check (rent >= 0),
    check (fee >= 0),
    check (bedrooms > 0),
    check (bathrooms > 0),
    check (sq_footage > 0),
    check (type in ('apartment','townhouse','single family house')),
    foreign key (owner) references PropOwner(name));

create table Lease
   (lease_num      	int 		not null unique,
    property_num   	int 		not null unique,
    addr           	varchar(100) 	not null,
    pay_method     	char(10) 	not null,
    deposit        	float(2) 	not null,
    startdate          	date 		not null,
    enddate            	date 		not null,
    rent           	float(2) 	not null,
    primary key (lease_num),
    check (deposit >= 0),
    check (rent >= 0),
    foreign key (property_num) references Property);

create table LeaseClientInfo
   (lease_num      	int 		not null,
    client_name    	varchar(32) 	not null,
    client_addr    	varchar(100) 	not null,
    primary key (client_name, client_addr),
    foreign key (lease_num) references Lease);

create table advertises
   (property_num   	int 		not null,
    newspaper_name 	varchar(32),
    the_date       	date 		not null,
    cost           	float(2) 	not null,
    primary key (property_num, newspaper_name),
    check (cost >= 0),
    foreign key (property_num) references Property,
    foreign key (newspaper_name) references Newspaper
			         on delete set null);

create table views
   (client_num     	int 		not null unique,
    property_num   	int 		not null unique,
    the_date       	date 		not null,
    comments       	varchar(200),
    client_addr    	varchar(100) 	not null,
    primary key (client_num, property_num),
    foreign key (client_num) references Client,
    foreign key (property_num) references Property);

create table obtains
   (lease_num      	int 		not null,
    client_num     	int 		not null unique,
    primary key (client_num),
    foreign key (lease_num) references Lease,
    foreign key (client_num) references Client);

/* An employee can work on up to 30 Leases */
create table works_on
   (lease_num      	int 		not null unique,
    emp_num        	int 		not null,
    primary key (lease_num),
    foreign key (lease_num) references Lease,
    foreign key (emp_num) references Employee);

create table rents
   (name           	varchar(64) 	not null,
    property_num   	int 		not null unique,
    primary key (property_num),
    foreign key (name) references PropOwner,
    foreign key (property_num) references Property);
