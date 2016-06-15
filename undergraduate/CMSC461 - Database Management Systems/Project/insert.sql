/* Build Entity Tables */

/* Populate Branch table */

insert into Branch	values ('123','John Daniels','Main St.','Pheonix','Arizona','85749','5204395817','5207893212','1200', to_date('2005/12/20','YYYY/MM/DD'));
insert into Branch	values ('124','Jim Bean','Oak St','Tulsa','Ohio','12345','4109874512','7896540123','1000', to_date('2004/12/12','YYYY/MM/DD'));
insert into Branch	values ('125','Chivas Regal','Palm Ave','Houston','Texas','85746','6104561232','6104561233','5000', to_date('2003/12/10','YYYY/MM/DD'));
insert into Branch	values ('126','Captain Morgan','Peach St','Key West','Florida','12341','7495236545','7495236544','200', to_date('2006/1/1','YYYY/MM/DD'));
insert into Branch	values ('127','Jimmy Dean','Porker Rd','New York','New York','12346','2124569889','2124569899','550', to_date('2006/2/2','YYYY/MM/DD'));

/* Populate Employee table */
insert into Employee	values ('1231','Supervisor','123','','John Daniels','120000.28','128 Fair St, Pheonix, AZ, 85749','M', to_date('1746/12/8','YYYY/MM/DD'));
insert into Employee	values ('1232','Associate','123','John Daniels','John Smith','65000','18 Roanoke, Pheonix, AZ, 85749','M', to_date('1956/12/8','YYYY/MM/DD'));
insert into Employee	values ('1233','Associate','123','John Daniels','Thomas Smith','35000','17 Ro, Pheonix, AZ, 85749','M', to_date('1976/12/8','YYYY/MM/DD'));
insert into Employee	values ('1241','Supervisor','124','','Jim Bean','125000','Elm St, Tulsa, Ohio, 12345','M', to_date('1800/12/9','YYYY/MM/DD'));
insert into Employee	values ('1242','Associate','124','Jim Bean','Joe Bob','45500','8th, Tulsa, Ohio, 12345','M', to_date('1966/4/5','YYYY/MM/DD'));
insert into Employee	values ('1243','Associate','124','Jim Bean','Jim Bob','55000','9th, Tulsa, Ohio, 12345','M', to_date('1965/3/4','YYYY/MM/DD'));
insert into Employee	values ('1251','Supervisor','125','','Chivas Regal','150000','45 Cool Std, Houston, TX, 85746','M', to_date('1776/7/8','YYYY/MM/DD'));
insert into Employee	values ('1252','Associate','125','Chivas Regal','Jason Marky','45000','5 Cool Std, Houston, TX, 85746','M', to_date('1776/7/9','YYYY/MM/DD'));
insert into Employee	values ('1253','Associate','125','Chivas Regal','Mark Megan','45500','6 Cool Std, Houston, TX, 85746','M', to_date('1776/7/10','YYYY/MM/DD'));
insert into Employee	values ('1261','Supervisor','126','','Captain Morgan','145000','Margaritaville, Key West, FL, 12341','M', to_date('1975/8/8','YYYY/MM/DD'));
insert into Employee	values ('1262','Associate','126','Captain Morgan','Josh Dun','45000','46 The St, Key West, FL, 12341','M', to_date('1981/12/25','YYYY/MM/DD'));
insert into Employee	values ('1263','Associate','126','Captain Morgan','Jon McNich','45000','45 The St, Key West, FL, 12341','M', to_date('1980/12/7','YYYY/MM/DD'));
insert into Employee	values ('1271','Supervisor','127','','Jimmy Dean','130000','45 Drunk Blvd, New York, NY, 12346','M', to_date('1965/12/22','YYYY/MM/DD'));
insert into Employee	values ('1272','Associate','127','Jimmy Dean','Kevin Mary','68000.25','15th St, New York, NY, 12346','M', to_date('1966/12/10','YYYY/MM/DD'));
insert into Employee	values ('1273','Associate','127','Jimmy Dean','Paul Trip','5.25','12 Loser St, New York, NY, 12346','M', to_date('1976/11/7','YYYY/MM/DD'));

/* Populate Newspaper table */
insert into Newspaper	values ('Baltimore Sun','4104395555','Pratt St, Baltimore, MD, 21250','4104396666','Charles Frasier');
insert into Newspaper	values ('Baltimore Gazette','4104375555','Fayette St, Baltimore, MD, 21250','4104376666','James Smith');
insert into Newspaper	values ('New York Times','2128884455','1st St, New York, NY, 12346','2128886655','The Man');

/* Populate PropOwner, PropOwnerTele, PropOwnerFax table */
insert into PropOwner	values ('Owner 1','Yes','North St, Ireland','','');
insert into PropOwner	values ('Owner 2','No','South St, Poland','George Smith','Rentals');
insert into PropOwnerTele values ('Owner 1','4104569878');
insert into PropOwnerTele values ('Owner 2','4109891212');
insert into PropOwnerFax  values ('Owner 1','4104569788');
insert into PropOwnerFax  values ('Owner 2','4109892121');

/* Populate Proerty table */
insert into Property	values ('321','Owner 1','450','10','2','5','1100','apartment','Elm St','Pheonix','Arizona','85749');
insert into Property	values ('322','Owner 1','450','10','2','5','1100','apartment','North St','Pheonix','Arizona','85749');
insert into Property	values ('323','Owner 2','450','10','5','5','3500','townhouse','1 South Blvd','New York','New York','12346');
insert into Property	values ('324','Owner 2','450','10','6','5','5600','single family house','11 South Blvd','New York','New York','12346');
insert into Property	values ('325','Owner 2','450','10','6','5','10000','single family house','12 South Blvd','New York','New York','12346');

/* Populate Client, ClientHomeTele, ClientWorkTele table */
insert into Client	values ('1','Buckaroo Bonzai','apartment','700','John Smith', to_date('2006/1/1','YYYY/MM/DD'),'123');
insert into Client	values ('2','New Jersey','townhouse','600','Joe Bob', to_date('2005/4/5','YYYY/MM/DD'),'124');
insert into Client	values ('3','Boyd Sheldon','single family house','1100','Kevin Mary', to_date('2005/7/1','YYYY/MM/DD'),'127');
insert into Client	values ('4','Foster Sheldon','apartment','4500','Jon McNich', to_date('2006/1/4','YYYY/MM/DD'),'126');
insert into ClientHomeTele values ('1','2221234565');
insert into ClientHomeTele values ('2','2223214444');
insert into ClientHomeTele values ('3','4444444445');
insert into ClientHomeTele values ('4','5546546654');
insert into ClientWorkTele values ('1','2221234488');
insert into ClientWorkTele values ('2','2222222100');
insert into ClientWorkTele values ('3','5444444444');
insert into ClientWorkTele values ('4','6666666666');

/* Populate Lease, LeaseClientInfo table */
insert into Lease	values ('789','321','Elm St, Pheonix, Arizona, 85749','Check','5500', to_date('2006/8/13','YYYY/MM/DD'), to_date('2007/1/1','YYYY/MM/DD'),'450.00');
insert into Lease	values ('790','322','North St, Pheonix, Arizona, 85749','Cash','1200', to_date('2006/8/12','YYYY/MM/DD'), to_date('2007/2/2','YYYY/MM/DD'),'450.00');
insert into Lease	values ('791','323','1 South Blvd, New York, New York, 12346','Cash','6500', to_date('2006/8/11','YYYY/MM/DD'), to_date('2007/3/5','YYYY/MM/DD'),'450.00');
insert into LeaseClientInfo values ('789','Buckaroo Bonzai','Jason Ave, Pheonix, Arizona, 85749');
insert into LeaseClientInfo values ('790','New Jersey','1st St, Tucson, Arizona, 85745');
insert into LeaseClientInfo values('791','Foster Sheldon','BackWoords, West Virginia');

/* Build Initial Relation Tables */

/* Populate advertises table */
insert into advertises	values ('321','Baltimore Sun', to_date('2007/5/6','YYYY/MM/DD'),'12.00');
insert into advertises	values ('321','Baltimore Gazette', to_date('2007/5/5','YYYY/MM/DD'),'15.00');
insert into advertises	values ('321','New York Times', to_date('2007/5/4','YYYY/MM/DD'),'17.00');
insert into advertises	values ('322','Baltimore Gazette', to_date('2007/5/5','YYYY/MM/DD'),'15.00');
insert into advertises	values ('322','New York Times', to_date('2007/5/5','YYYY/MM/DD'),'15.00');
insert into advertises	values ('323','New York Times', to_date('2007/5/3','YYYY/MM/DD'),'15.00');

/* Populate views table */
insert into views	values ('3','325', to_date('2006/8/15','YYYY/MM/DD'),'Potential Buy','52nd Blvd, Queens, New York, 12346');

/* Populate obtains table */
insert into obtains	values ('789','1');
insert into obtains	values ('790','2');
insert into obtains	values ('791','4');

/* Populate works_on table */
insert into works_on	values ('789','1232');
insert into works_on	values ('790','1242');
insert into works_on	values ('791','1262');

/* Populate rents table */
/* This table may be redundant */
insert into rents	values ('Owner 1','321');
insert into rents	values ('Owner 1','322');
insert into rents	values ('Owner 2','323');
insert into rents	values ('Owner 2','324');
insert into rents	values ('Owner 2','325');

