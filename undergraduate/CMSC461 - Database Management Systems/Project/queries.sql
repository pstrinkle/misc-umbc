1.	select * from Branch where addr_city = 'Tulsa';
2.	select count(branch_num) from Branch where addr_st = 'Ohio';
3.	select name,position,salary from Employee where branch_num = 123 order by name;
4.	select sum(salary), count(emp_num) from Employee;
5.	select count(emp_num),position from Employee where Employee.branch_num in
		(select branch_num from Branch where Branch.addr_city = 'New York' and Branch.addr_st = 'New York')
		group by position;
6.	select manager from Branch order by addr_st,addr_city,addr_str;
7.	select name from Employee where position = 'Associate' and supervisor = 'John Daniels';
8.	select * from Property,PropOwner,PropOwnerTele,PropOwnerFax where
		Property.owner = PropOwner.name and PropOwner.name = PropOwnerTele.name and
		PropOwner.name = PropOwnerFax.name and Property.addr_city = 'Pheonix' order by Property.rent;
9.	select * from Property where property_num in
		(select property_num from Employee,Lease,works_on where Employee.emp_num = works_on.emp_num and
		works_on.lease_num = Lease.lease_num and Employee.branch_num = 123);
10.	select * from Property where property_num in
		(select rents.property_num from PropOwner,rents,Lease,works_on,Employee where
		PropOwner.name = rents.name and
		rents.property_num = Lease.property_num and
		Lease.lease_num = works_on.lease_num and
		works_on.emp_num = Employee.emp_num and
		Employee.branch_num = 126 and
		PropOwner.private = 'No');
11.	select count(property_num),type from Property group by type;
12.
13.	select * from Property where type = 'apartment' and bedrooms >= 2 and addr_city = 'Baltimore' and addr_st = 'MD' and rent <= 1200;
14.	select * from Client where client_num not in (select client_num from obtains);
15.	select * from PropOwner where name in (select name from rents where property_num = 321);
16.	select comments from views where property_num = 325;
17.
18.	select * from Lease where enddate < add_months(sysdate,1) and lease_num in
		(select lease_num from works_on,Employee where works_on.emp_num = Employee.emp_num and
		Employee.branch_num = 123);
19.	select count(lease_num),addr_st from Lease,Property where Lease.property_num = Property.property_num and enddate
		- startdate < 12 * 31 group by Property.addr_st;
20.	select sum(rent),sum(fee) from Property where property_num in (select property_num from Lease);
	select sum(salary) from (select distinct emp_num,salary from Employee);
	select sum(rent),sum(fee) from Property;
21.	select * from Lease,Property where enddate <= add_months(sysdate,-3) and Lease.property_num = Property.property_num
22.	select * from Client,ClientHomeTele,ClientWorkTele where Client.client_num = ClientHomeTele.client_num and
		Client.client_num = ClientWorkTele.client_num and preference in
			(select type from Property where Property.property_num = 321);