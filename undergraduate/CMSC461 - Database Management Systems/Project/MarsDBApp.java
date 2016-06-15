/*
 * Main.java
 *
 * Created on August 12, 2006, 7:54 AM
 *
 * To change this template, choose Tools | Options and locate the template under
 * the Source Creation and Management node. Right-click the template and choose
 * Open. You can then make changes to the template in the Source Editor.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.*;

/**
 *
 * @author Patrick Trinkle
 * CMSC461 Database Management Systems
 * Summer 2006
 *
 */
public class MarsDBApp {
    
    /** Creates a new instance of Main */
    public MarsDBApp() {
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        
        String fakeuser, fakepasswd;
        
        System.out.println("\tMars Reality Database System");
        System.out.print("Enter Username: ");
        fakeuser = stdIn.readLine();
        System.out.print("Enter Password: ");
        fakepasswd = stdIn.readLine();
        
        userLogin = "tri1";
        userPasswd = "tri1";
        
        
        int choice = 0;
        while (choice != 5) {
            
            System.out.println("\tMars Reality Database System Main Menu");
            System.out.println("1 - Enter New Data\n2 - Update Data\n3 - Delete Data\n4 - Query/Report Data\n5 - Exit");
            System.out.print("Enter Option: ");
            choice = Integer.parseInt(stdIn.readLine());
            
            switch(choice) {
                case 1:
                    enterData();
                    break;
                case 2:
                    updateData();
                    break;
                case 3:
                    deleteData();
                    break;
                case 4:
                    generateReports();
                    break;
                case 5:
                    break;
                default:
                    System.out.println("Invalid");
                    break;
            }
        }
    }
    
    /* Enter data takes employee numbers, branch numbers, etc, of that type as String
     * Most of the additions and updates and deletes have SQL behind them
     * to make sure they go through smoothly.
     */
    public static void enterData() throws IOException{
        
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        
        int choice = 0;
        while (choice != 9) {
            
            System.out.println("\tEnter Data");
            System.out.println("1 - Enter a new Branch\n2 - Enter a new Employee\n3 - Enter a new Client\n4 - Enter a new Property Owner\n5 - Enter a new Property\n6 - Enter a new Lease\n7 - Enter a new Advertisement\n8 - Enter a new Viewing\n9 - Back");
            System.out.print("Enter Option: ");
            choice = Integer.parseInt(stdIn.readLine());
            
            switch(choice) {
                case 1:
                    addBranch();
                    break;
                case 2:
                    addEmployee();
                    break;
                case 3:
                    addClient();
                    break;
                case 4:
                    addOwner();
                    break;
                case 5:
                    addProperty();
                    break;
                case 6:
                    addLease();
                    break;
                case 7:
                    addAdvertisement();
                    break;
                case 8:
                    addViewing();
                    break;
                case 9:
                    return;
                default:
                    System.out.println("Invalid Option");
                    break;
            }
        }
    }
    public static void addBranch() throws IOException{
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        
        System.out.println("\tEnter a new Branch");
        System.out.print("Enter (Unique) Branch Number: ");
        int branch_num = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter State (Spelled out): ");
        String addr_st = stdIn.readLine();
        System.out.print("Enter City: ");
        String addr_city = stdIn.readLine();
        System.out.print("Enter Street Address: ");
        String addr_str = stdIn.readLine();
        System.out.print("Enter zip code: ");
        String addr_zip = stdIn.readLine();
        System.out.print("Enter telephone number (numbers only): ");
        String tele = stdIn.readLine();
        System.out.print("Enter fax number (numbers only): ");
        String fax = stdIn.readLine();
        System.out.print("Enter manager's monthly bonus (numbers only): ");
        int monthly_bonus = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter manager's name (first last): ");
        String manager = stdIn.readLine();
        System.out.print("Enter the date this manager started (YYYY/MM/DD): ");
        String start = stdIn.readLine();
        
        String firstbit = "insert into Branch values (";
        String endbit = "',to_date('" + start + "','YYYY/MM/DD'))";
        String middlebit = "'" + branch_num + "','" + manager + "','" + addr_str + "','" + addr_city + "','" + addr_st + "','" + addr_zip + "','" + fax + "','" + tele + "','" + monthly_bonus;
        String insert = firstbit + middlebit + endbit;
        
        execute(insert);
    }
    public static void addEmployee() throws IOException{
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        
        System.out.println("\tEnter a new employee");
        System.out.print("Enter (Unique) Employee Number: ");
        int emp_num = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter Position (Associate|Supervisor): ");
        String position = stdIn.readLine();
        System.out.print("Enter Branch Number: ");
        String branch_num = stdIn.readLine();
        System.out.print("Enter Name (first last): ");
        String name = stdIn.readLine();
        System.out.print("Enter Gender (M|F): ");
        String sex = stdIn.readLine();
        System.out.print("Enter salary (numbers only): ");
        double salary = Double.parseDouble(stdIn.readLine());
        System.out.print("Enter address: ");
        String addr = stdIn.readLine();
        System.out.print("Do you have a supervisor (y|n)? ");
        String answer = stdIn.readLine();
        String supervisor = "";
        
        if (answer == "y") {
            System.out.print("Enter supervisor's name: ");
            supervisor = stdIn.readLine();
        }
        
        System.out.print("Enter date of birth (YYYY/MM/DD): ");
        String dob = stdIn.readLine();
        
        String firstbit = "insert into Employee values('";
        String middlebit = emp_num + "','" + position + "','" + branch_num + "','" + supervisor + "','" + name + "','" + salary + "','" + addr + "','" + sex;
        String endbit = "',to_date('" + dob + "','YYYY/MM/DD'))";
        String insert = firstbit + middlebit + endbit;
        
        execute(insert);
    }
    public static void addClient() throws IOException{
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        
        System.out.println("\tEnter a new Client");
        System.out.print("Enter (Unique) Client Number: ");
        int client_num = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter Client Name (first last): ");
        String name = stdIn.readLine();
        System.out.print("Enter Client's Preference (apartment|townhouse|single family house): ");
        String preference = stdIn.readLine();
        System.out.print("Enter maximum rent (numbers only): ");
        int max_rent = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter name of employee processing client (first last): ");
        String employee_name = stdIn.readLine();
        System.out.print("Enter date joined (YYYY/MM/DD): ");
        String joined = stdIn.readLine();
        System.out.print("Enter branch joined: ");
        int branch_num = Integer.parseInt(stdIn.readLine());
        
        String firstbit = "insert into Client values ('";
        String middlebit = client_num + "','" + name + "','" + preference + "','" + max_rent + "','" + employee_name + "',";
        String endbit = "to_date('" + joined + "','YYYY/MM/DD'),'" + branch_num + "')";
        String insert = firstbit + middlebit + endbit;
        
        execute(insert);
        
        int i = 0;
        
        System.out.print("How many home telephone numbers does Client have: ");
        int x = Integer.parseInt(stdIn.readLine());
        for (i = 0; i < x; ++i) {
            System.out.print("Enter hometelephone number: ");
            String home_num = stdIn.readLine();
            execute("insert into ClientHomeTele values ('" + client_num + "','" + home_num + "')");
        }
        
        System.out.print("How many work telephone numbers does Client have: ");
        x = Integer.parseInt(stdIn.readLine());
        for (i = 0; i < x; ++i) {
            System.out.print("Enter work telephone number: ");
            String work_num = stdIn.readLine();
            execute("insert into ClientWorkTele values ('" + client_num + "','" + work_num + "')");
        }
        
    }
    public static void addOwner() throws IOException{
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        
        System.out.println("\tEnter a new Owner");
        System.out.print("Enter (Unique) Owner Name: ");
        String name = stdIn.readLine();
        System.out.print("Enter address: ");
        String addr = stdIn.readLine();
        System.out.print("Is this a Private or Business Owner (p|b)? ");
        String answer = stdIn.readLine();
        String contact = "";
        String type = "";
        
        if (answer == "b") {
            System.out.print("Enter contact name (first last): ");
            contact = stdIn.readLine();
            System.out.print("Enter the type of business: ");
            type = stdIn.readLine();
        }
        
        if (answer == "b") {
            answer = "No";
        } else {
            answer = "Yes";
        }
        
        String firstbit = "insert into PropOwner values ('";
        String middlebit = name + "','" + answer + "','" + addr + "','" + contact + "','" + type + "')";
        String insert = firstbit + middlebit;
        execute(insert);
        
        int i = 0;
        
        System.out.print("How many telephone numbers does the Owner have: ");
        int x = Integer.parseInt(stdIn.readLine());
        for (i = 0; i < x; ++i) {
            System.out.print("Enter telephone number: ");
            String tele = stdIn.readLine();
            execute("insert into PropOwnerTele values ('"  + name + "','" + tele + "')");            
        }
                        
        String fax = "";
                
        System.out.print("How many fax numbers does the Owner have: ");
        x = Integer.parseInt(stdIn.readLine());
        for (i = 0; i < x; ++i) {            
            System.out.print("Enter fax number: ");
            fax = stdIn.readLine();
            execute("insert into PropOwnerFax values ('" + name + "','" + fax + "')");
        }        
    }
    public static void addProperty() throws IOException{
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        
        System.out.println("\tEnter a new Property");
        System.out.print("Enter (Unique) Property Number: ");
        int property_num = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter Owner Name: ");
        String owner = stdIn.readLine();
        System.out.print("Enter Monthly Rent: ");
        int rent = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter Monthly Fee: ");
        int fee = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter Number of Bedrooms: ");
        int bedrooms = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter Number of Bathrooms: ");
        int bathrooms = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter Square Footage: ");
        int sq_footage = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter Type (apartment|townhouse|single family house): ");
        String type = stdIn.readLine();
        System.out.print("Enter Street: ");
        String addr_str = stdIn.readLine();
        System.out.print("Enter City: ");
        String addr_city = stdIn.readLine();
        System.out.print("Enter State: ");
        String addr_st = stdIn.readLine();
        System.out.print("Enter Zipcode: ");
        String addr_zip = stdIn.readLine();
        
        String firstbit = "insert into Property values ('";
        String middlebit = property_num + "','" + owner + "','" + rent + "','" + fee + "','" + bedrooms + "','" + bathrooms + "','" + sq_footage + "','" + type + "','" + addr_str + "','" + addr_city + "','" + addr_st + "','" + addr_zip + "')";
        String insert = firstbit + middlebit;
        
        execute(insert);
    }
    public static void addLease() throws IOException{
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        
        System.out.println("\tEnter a new Lease");
        System.out.print("Enter (Unique) Lease Number: ");
        int lease_num = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter (Unique) Property Number: ");
        int property_num = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter address: ");
        String addr = stdIn.readLine();
        System.out.print("Enter Payment Method: ");
        String pay_method = stdIn.readLine();
        System.out.print("Enter Deposit: ");
        double deposit = Double.parseDouble(stdIn.readLine());
        System.out.print("Enter Monthly Rent: ");
        double rent = Double.parseDouble(stdIn.readLine());
        System.out.print("Enter Start Date (YYYY/MM/DD): ");
        int start = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter End Date (YYYY/MM/DD): ");
        int end = Integer.parseInt(stdIn.readLine());
        
        String firstbit = "insert into Lease values ('";
        String middlebit = lease_num + "','" + property_num + "','" + addr + "','" + pay_method + "','" + deposit + "',";
        String endbit = "to_date('" + start + "','YYYY/MM/DD')," + "to_date('" + end + "','YYYY/MM/DD''),'" + rent + "')";
        String insert = firstbit + middlebit + endbit;
        
        execute(insert);
    }
    public static void addAdvertisement() throws IOException{
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        
        System.out.println("\tEnter a new advertisement:");
        System.out.print("Enter (Unique) Newspaper Name: ");
        String newspaper_name = stdIn.readLine();
        System.out.print("Enter (Unique) Property Number: ");
        int property_num = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter the Date (YYYY/MM/DD): ");
        String thedate = stdIn.readLine();
        System.out.print("Enter the Cost (numbers only): ");
        double cost = Double.parseDouble(stdIn.readLine());
        
        String firstbit = "insert into advertises values ('";
        String middlebit = property_num + "','" + newspaper_name + "',to_date('" + thedate + "','YYYY/MM/DD'),'" + cost + "')";
        String insert = firstbit + middlebit;
        
        execute(insert);
    }
    public static void addViewing() throws IOException{
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        
        System.out.println("\tEnter a new viewing:");
        System.out.print("Enter (Unique) Client Number: ");
        int client_num = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter (Unique) Property Number: ");
        int property_num = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter the Date (YYYY/MM/DD): ");
        String thedate = stdIn.readLine();
        System.out.print("Enter Comments: ");
        String comments = stdIn.readLine();
        System.out.print("Enter Client's Address: ");
        String client_addr = stdIn.readLine();
        
        String firstbit = "insert into views values ('";
        String middlebit = client_num + "','" + property_num + "',to_date('" + thedate + "','YYYY/MM/DD'),'" + comments + "','" + client_addr + "')";
        String insert = firstbit + middlebit;
        
        execute(insert);
    }
    
    public static void updateData() throws IOException{
        
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        
        int choice = 0;
        while (choice != 8) {
            
            System.out.println("\tUpdate Data");
            System.out.println("1 - Branch Details\n2 - Employee Details\n3 - Lease Details\n4 - Advertisement Details\n5 - Owner Details\n6 - Property Details\n7 - Client Details\n8 - Back");
            System.out.println("Enter Option:");
            choice = Integer.parseInt(stdIn.readLine());
            
            switch(choice) {
                case 1:
                    System.out.print("Enter the Branch Number you'd like to update: ");
                    int branch_num = Integer.parseInt(stdIn.readLine());
                    updateBranch(branch_num);
                    break;
                case 2:
                    System.out.print("Enter the Employee Number you'd like to update: ");
                    int emp_num = Integer.parseInt(stdIn.readLine());
                    updateEmployee(emp_num);
                    break;
                case 3:
                    System.out.print("Enter the Lease Number you'd like to update: ");
                    int lease_num = Integer.parseInt(stdIn.readLine());
                    updateLease(lease_num);
                    break;
                case 4:
                    System.out.print("Enter Newspaper Name: ");
                    String newspaper_name = stdIn.readLine();
                    System.out.print("Enter Property Number: ");
                    int property_num = Integer.parseInt(stdIn.readLine());
                    updateAdvertisement(newspaper_name, property_num);
                    break;
                case 5:
                    System.out.print("Enter Owner Name you'd like to update: ");
                    String name = stdIn.readLine();
                    updateOwner(name);
                    break;
                case 6:
                    System.out.print("Enter Property Number you'd like to update: ");
                    property_num = Integer.parseInt(stdIn.readLine());
                    updateProperty(property_num);
                    break;
                case 7:
                    System.out.print("Enter Client Number you'd like to update: ");
                    int client_num = Integer.parseInt(stdIn.readLine());
                    updateClient(client_num);
                    break;
                case 8:
                    return;
                default:
                    System.out.println("Invalid Input");
                    break;
            }
        }
    }
    public static void updateBranch(int branch_num) throws IOException{
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Current information stored for Branch: " + branch_num);
        executequery("select * from Branch where branch_num = " + branch_num);
        
        System.out.println("Enter in the following information, you can copy and paste from above");
        System.out.print("Enter State (Spelled out): ");
        String addr_st = stdIn.readLine();
        System.out.print("Enter City: ");
        String addr_city = stdIn.readLine();
        System.out.print("Enter Street Address: ");
        String addr_str = stdIn.readLine();
        System.out.print("Enter zip code: ");
        String addr_zip = stdIn.readLine();
        System.out.print("Enter telephone number (numbers only): ");
        String tele = stdIn.readLine();
        System.out.print("Enter fax number (numbers only): ");
        String fax = stdIn.readLine();
        System.out.print("Enter manager's monthly bonus (numbers only): ");
        int monthly_bonus = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter manager's name (first last): ");
        String manager = stdIn.readLine();
        System.out.print("Enter the date this manager started (YYYY/MM/DD): ");
        String start = stdIn.readLine();
        
        // update line
        // I couldn't find good documentation on doing this in one line. so here it goes.
        execute("update Branch set addr_st = '" + addr_st + "' where branch_num = " + branch_num);
        execute("update Branch set addr_city = '" + addr_city + "' where branch_num = " + branch_num);
        execute("update Branch set addr_str = '" + addr_str + "' where branch_num = " + branch_num);
        execute("update Branch set addr_zip = '" + addr_zip + "' where branch_num = " + branch_num);
        execute("update Branch set tele = '" + tele + "' where branch_num = " + branch_num);
        execute("update Branch set fax = '" + fax + "' where branch_num = " + branch_num);
        execute("update Branch set monthly_bonus = '" + monthly_bonus + "' where branch_num = " + branch_num);
        execute("update Branch set manager = '" + manager + "' where branch_num = " + branch_num);
        execute("update Branch set manager_start = to_date('" + start + "','YYYY/MM/DD') where branch_num = " + branch_num);
    }
    public static void updateEmployee(int emp_num) throws IOException{
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Current information stored for Employee: " + emp_num);
        executequery("select * from Employee where emp_num = " + emp_num);
        
        System.out.println("Enter in the following information, you can copy and paste from above");
        System.out.print("Enter Position (Associate|Supervisor): ");
        String position = stdIn.readLine();
        System.out.print("Enter Branch Number: ");
        String branch_num = stdIn.readLine();
        System.out.print("Enter Name (first last): ");
        String name = stdIn.readLine();
        System.out.print("Enter Gender (M|F): ");
        String sex = stdIn.readLine();
        System.out.print("Enter salary (numbers only): ");
        double salary = Double.parseDouble(stdIn.readLine());
        System.out.print("Enter address: ");
        String addr = stdIn.readLine();
        System.out.print("Do you have a supervisor (y|n)? ");
        String answer = stdIn.readLine();
        String supervisor = "";
        
        if (answer == "y") {
            System.out.print("Enter supervisor's name: ");
            supervisor = stdIn.readLine();
        }
        
        System.out.print("Enter date of birth (YYYY/MM/DD): ");
        String dob = stdIn.readLine();
        
        //update query
        execute("update Employee set position = " + position + " where emp_num = " + emp_num);
        execute("update Employee set branch_num = " + branch_num + " where emp_num = " + emp_num);
        
        if (answer == "y") {
            execute("update Employee set supervisor = '" + supervisor + "' where emp_num = " + emp_num);
        }
        execute("update Employee set name = '" + name + "' where emp_num = " + emp_num);
        execute("update Employee set salary = " + salary + " where emp_num = " + emp_num);
        execute("update Employee set addr = '" + addr + "' where emp_num = " + emp_num);
        execute("update Employee set sex = " + sex + " where emp_num = " + emp_num);
        execute("update Employee set dob = to_date('" + dob + "','YYYY/MM/DD') where emp_num = " + emp_num);
    }
    public static void updateLease(int lease_num) throws IOException{
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Current information stored for Lease: " + lease_num);
        executequery("select * from Lease where lease_num = " + lease_num);
        
        System.out.print("Enter (Unique) Property Number: ");
        int property_num = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter address: ");
        String addr = stdIn.readLine();
        System.out.print("Enter Payment Method: ");
        String pay_method = stdIn.readLine();
        System.out.print("Enter Deposit: ");
        double deposit = Double.parseDouble(stdIn.readLine());
        System.out.print("Enter Monthly Rent: ");
        double rent = Double.parseDouble(stdIn.readLine());
        System.out.print("Enter Start Date (YYYY/MM/DD): ");
        int start = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter End Date (YYYY/MM/DD): ");
        int end = Integer.parseInt(stdIn.readLine());
        
        //update query
        execute("update Lease set property_num = " + property_num + " where lease_num = " + lease_num);
        execute("update Lease set addr = '" + addr + "' where lease_num = " + lease_num);
        execute("update Lease set pay_method = '" + pay_method + "' where lease_num = " + lease_num);
        execute("update Lease set deposit = " + deposit + " where lease_num = " + lease_num);
        execute("update Lease set rent = " + rent + " where lease_num = " + lease_num);
        execute("update Lease set startdate = to_date('" + start + "','YYYY/MM/DD') where lease_num = " + lease_num);
        execute("update Lease set endtdate = to_date('" + end + "','YYYY/MM/DD') where lease_num = " + lease_num);
    }
    public static void updateAdvertisement(String newspaper_name, int property_num) throws IOException{
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Current information stored for Newspaper Advertisement");
        executequery("select * from advertises where property_num = " + property_num + " and newspaper_name = " + newspaper_name);
        
        System.out.print("Enter the Date (YYYY/MM/DD): ");
        String thedate = stdIn.readLine();
        System.out.print("Enter the Cost (numbers only): ");
        double cost = Double.parseDouble(stdIn.readLine());
        
        //update advertises
        execute("update advertises set the_date = to_date('" + thedate + "','YYYY/MM/DD') where newspaper_name = " + newspaper_name + " and property_num = " + property_num);
        execute("update advertises set cost = " + cost + " where newspaper_name = " + newspaper_name + " and property_num = " + property_num);
    }
    public static void updateOwner(String name) throws IOException{
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Current information stored for Owner: " + name);
        executequery("select * from PropOwner,PropOwnerTele,PropOwnerFax where PropOwner.name = " + name + " and PropOwner.name = PropOwnerTele.name and PropOwnerFax.name = PropOwner.name");
        
        System.out.print("Enter address: ");
        String addr = stdIn.readLine();
        System.out.print("Enter telephone number: ");
        String tele = stdIn.readLine();
        System.out.print("Is there a fax number (y|n)? ");
        String yesno = stdIn.readLine();
        
        String fax = "";
        
        if (yesno == "y") {
            System.out.print("Enter fax number: ");
            fax = stdIn.readLine();
        }
        
        System.out.print("Is this a Private or Business Owner (p|b)? ");
        String answer = stdIn.readLine();
        String contact = "";
        String type = "";
        
        if (answer == "b") {
            System.out.print("Enter contact name (first last): ");
            contact = stdIn.readLine();
            
            System.out.print("Enter the type of business: ");
            type = stdIn.readLine();
        }
        
        if (answer == "b") {
            answer = "No";
        } else {
            answer = "Yes";
        }
        
        //update PropOwner
        execute("update PropOwner set addr = " + addr + " where name = " + name);
        execute("update PropOwner set private = " + answer + " where name = " + name);
        
        if (answer.equalsIgnoreCase("No")) {
            execute("update PropOwner set contact = " + contact + " where name = " + name);
            execute("update PropOwner set type = " + type + " where name = " + name);
        }
        
        //update PropOwnerTele
        execute("update PropOwnerTele set tele = " + tele + " where name = " + name);
        
        //update PropOwnerFax
        if (yesno == "y") {
            execute("update PropOwnerFax set fax = " + fax + " where name = " + name);
        }
    }
    public static void updateProperty(int property_num) throws IOException{
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Current information stored for Property: " + property_num);
        executequery("select * from Property where property_num = " + property_num);
        
        System.out.print("Enter Owner Name: ");
        String owner = stdIn.readLine();
        System.out.print("Enter Monthly Rent: ");
        int rent = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter Monthly Fee: ");
        int fee = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter Number of Bedrooms: ");
        int bedrooms = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter Number of Bathrooms: ");
        int bathrooms = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter Square Footage: ");
        int sq_footage = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter Type (apartment|townhouse|single family house): ");
        String type = stdIn.readLine();
        System.out.print("Enter Street: ");
        String addr_str = stdIn.readLine();
        System.out.print("Enter City: ");
        String addr_city = stdIn.readLine();
        System.out.print("Enter State: ");
        String addr_st = stdIn.readLine();
        System.out.print("Enter Zipcode: ");
        String addr_zip = stdIn.readLine();
        
        //update Property
        execute("update Property set owner = '" + owner + "' where property_num = " + property_num);
        execute("update Property set rent = " + rent + " where property_num = " + property_num);
        execute("update Property set fee = " + fee + " where property_num = " + property_num);
        execute("update Property set bedrooms = " + bedrooms + " where property_num = " + property_num);
        execute("update Property set bathrooms = " + bathrooms + " where property_num = " + property_num);
        execute("update Property set sq_footage = " + sq_footage + " where property_num = " + property_num);
        execute("update Property set type = " + type + " where property_num = " + property_num);
        execute("update Property set addr_str = '" + addr_str + "' where property_num = " + property_num);
        execute("update Property set addr_city = '" + addr_city + "' where property_num = " + property_num);
        execute("update Property set addr_st = '" + addr_st + "' where property_num = " + property_num);
        execute("update Property set addr_zip = '" + addr_zip + "' where property_num = " + property_num);
    }
    public static void updateClient(int client_num) throws IOException{
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Current information stored for Client: " + client_num);
        executequery("select * from Client,ClientHomeTele,ClientWorkTele where Client.client_num = " + client_num + " and Client.client_num = ClientHomeTele.client_num and ClientWorkTele.client_num = Client.client_num");
        
        System.out.print("Enter Client Name (first last): ");
        String name = stdIn.readLine();
        System.out.print("Enter Client's Preference (apartment|townhouse|single family house): ");
        String preference = stdIn.readLine();
        System.out.print("Enter maximum rent (numbers only): ");
        int max_rent = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter name of employee processing client (first last): ");
        String employee_name = stdIn.readLine();
        System.out.print("Enter date joined (YYYY/MM/DD): ");
        String joined = stdIn.readLine();
        System.out.print("Enter branch joined: ");
        int branch_num = Integer.parseInt(stdIn.readLine());
        System.out.print("Enter home telephone number: ");
        String home_num = stdIn.readLine();
        System.out.print("Enter work telephone number: ");
        String work_num = stdIn.readLine();
        
        //update Client
        execute("update Client set name = '" + name + "' where client_num = " + client_num);
        execute("update Client set preference = '" + preference + "' where client_num = " + client_num);
        execute("update Client set max_rent = " + max_rent + " where client_num = " + client_num);
        execute("update Client set employee_name = '" + employee_name + "' where client_num = " + client_num);
        execute("update Client set date_joined = to_date('" + joined + "','YYYY/MM/DD') where client_num = " + client_num);
        execute("update Client set branch_joined = " + branch_num + " where client_num = " + client_num);
        
        //update ClientHomeTele
        execute("update ClientHomeTele set home_tele = " + home_num + " where client_num = " + client_num);
        //update ClientWorkTele
        execute("update ClientWorkTele set work_tele = " + work_num + " where client_num = " + client_num);
    }
    
    public static void deleteData() throws IOException{
        
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        
        int choice = 0;
        while (choice != 8) {
            
            System.out.println("\tDelete Data");
            System.out.println("1 - Branch\n2 - Employee\n3 - Lease\n4 - Advertisement\n5 - Owner\n6 - Property\n7 - Client\n8 - Back");
            System.out.print("Enter Option: ");
            choice = Integer.parseInt(stdIn.readLine());
            
            switch(choice) {
                case 1:
                    System.out.println("\tDeleting Branch from System");
                    System.out.println("All references to this Branch will be set to null.");
                    System.out.print("\nEnter Branch Number: ");
                    int branch_num = Integer.parseInt(stdIn.readLine());
                    System.out.println();
                    deleteBranch(branch_num);
                    break;
                case 2:
                    System.out.println("\tDeleting Employee from System");
                    System.out.print("Enter Employee Number: ");
                    int emp_num = Integer.parseInt(stdIn.readLine());
                    System.out.println();
                    deleteEmployee(emp_num);
                    break;
                case 3:
                    System.out.println("\tDeleting Lease from System");
                    System.out.print("Enter Lease Number: ");
                    int lease_num = Integer.parseInt(stdIn.readLine());
                    System.out.println();
                    deleteLease(lease_num);
                    break;
                case 4:
                    System.out.println("\tDeleting Advertisement from System");
                    System.out.print("Enter Newspaper Name: ");
                    String newspaper_name = stdIn.readLine();
                    System.out.print("Enter Property Number: ");
                    int property_num = Integer.parseInt(stdIn.readLine());
                    System.out.println();
                    deleteAdvertisement(newspaper_name, property_num);
                    break;
                case 5:
                    System.out.println("\tDeleting Owner from System");
                    System.out.println("This will also remove all associated Property");
                    System.out.print("Enter Owner Name: ");
                    String name = stdIn.readLine();
                    System.out.println();
                    deleteOwner(name);
                    break;
                case 6:
                    System.out.println("\tDeleting Property from System");
                    System.out.print("Enter Property Number:");
                    property_num = Integer.parseInt(stdIn.readLine());
                    System.out.println();
                    deleteProperty(property_num);
                    break;
                case 7:
                    System.out.println("\tDeleting Client from System");
                    System.out.print("Enter Client Number: ");
                    int client_num = Integer.parseInt(stdIn.readLine());
                    System.out.println();
                    deleteClient(client_num);
                    break;
                case 8:
                    return;
                default:
                    break;
            }
        }
    }
    public static void deleteBranch(int branch_num) throws IOException{
        String clearEmployees = "delete from Employee where branch_num = " + branch_num;
        String query = "delete from Branch where branch_num = " + branch_num;
        
        execute(clearEmployees);
        execute(query);
    }
    public static void deleteEmployee(int emp_num) throws IOException{
        String clearworks_on = "delete from works_on where emp_num = " + emp_num;
        String query = "delete from Employee where emp_num = " + emp_num;
        
        execute(clearworks_on);
        execute(query);
    }
    public static void deleteLease(int lease_num) throws IOException{
        String clearLeaseClientInfo = "delete from LeaseClientInfo where lease_num = " + lease_num;
        String clearobtains = "delete from obtains where lease_num = " + lease_num;
        String clearworks_on = "delete from works_on where lease_num = " + lease_num;
        String query = "delete from Lease where lease_num = " + lease_num;
        
        execute(clearLeaseClientInfo);
        execute(clearobtains);
        execute(clearworks_on);
        execute(query);
    }
    public static void deleteAdvertisement(String newspaper_name, int property_num) throws IOException{
        String query = "delete from advertises where newspaper_name = " + newspaper_name + " and property_num = " + property_num;
        execute(query);
    }
    public static void deleteOwner(String name) throws IOException{
        String clearPropOwnerTele = "delete from PropOwnerTele where name = " + name;
        String clearPropOwnerFax = "delete from PropOwnerFax where name = " + name;
        String clearProperty = "delete from Property where owner = " + name;
        String rents = "delete from rents where name = " + name;
        String clearPropOwner = "delete from PropOwner where name = " + name;
        
        execute(clearPropOwnerTele);
        execute(clearPropOwnerFax);
        execute(clearProperty);
        execute(rents);
        execute(clearPropOwner);
    }
    public static void deleteProperty(int property_num) throws IOException{
        String Lease = "delete from Lease where property_num = " + property_num;
        String advertises = "delete from advertises where property_num = " + property_num;
        String views = "delete from views where property_num = " + property_num;
        String rents = "delete from rents where property_num = " + property_num;
        String query = "delete from Property where property_num = " + property_num;
        
        execute(Lease);
        execute(advertises);
        execute(views);
        execute(rents);
        execute(query);
    }
    public static void deleteClient(int client_num) throws IOException{
        String ClientHomeTele = "delete from ClientWorkTele where client_num = " + client_num;
        String ClientWorkTele = "delete from ClientHomeTele where client_num = " + client_num;
        String views = "delete from views where client_num = " + client_num;
        String obtains = "delete from obtains where client_num = " + client_num;
        String query = "delete from Client where client_num = " + client_num;
        
        execute(ClientHomeTele);
        execute(ClientWorkTele);
        execute(views);
        execute(obtains);
        execute(query);
    }
    
    public static void generateReports() throws IOException{
        
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        
        System.out.println("\tGenerate Reports");
        System.out.println("1 - List the details of branches in a given city.");
        System.out.println("2 - Find the total number of branches in a given state.");
        System.out.println("3 - List name, position, and salary of all employees at a given branch, ordered by name.");
        System.out.println("4 - Find the total number of employees and the sum of their salaries.");
        System.out.println("5 - List the number of employees in each position at branches in Baltimore, MD.");
        System.out.println("6 - List the name of branch managers, ordered by branch address.");
        System.out.println("7 - List the names of associates supervised by a given supervisor.");
        System.out.println("8 - List the details of properties in a given city, along with their owners’s details,\n\tordered by rent.");
        System.out.println("9 - List the details of properties for rent assigned to each associate at a given branch.");
        System.out.println("10 - List the details of properties provided by business owners at a given branch.");
        System.out.println("11 - Find the total number of properties of each type at all branches.");
        System.out.println("12 - List the details of private property owners that provide more than one property for rent.");
        System.out.println("13 - List the details of apartments with at least two bedrooms in Baltimore,\n\tMD with a monthly rent of at most $1200.");
        System.out.println("14 - List the details of clients registered at a branch, together with their preferences,\n\twhich have not signed a lease yet.");
        System.out.println("15 - List the details of the owner of a given property.");
        System.out.println("16 - List the comments made by clients that viewed a given property.");
        System.out.println("17 - Find those properties that have been advertised more than the average number of times.");
        System.out.println("18 - List the details of leases due to expire next month at a given branch.");
        System.out.println("19 - For each state, list the total number of leases with rental duration less than 12 months.");
        System.out.println("20 - Find the total current monthly rental income, total monthly management fees, total salaries,\n\tas well as the maximum possible monthly rental income and management fee.");
        System.out.println("21 - List the details of properties that have not been rented out for the last three months.");
        System.out.println("22 - List the details of clients whose preferences match a given property.");
        System.out.print("Enter Option: ");
        int choice = Integer.parseInt(stdIn.readLine());
        
        switch(choice) {
            case 1:
                System.out.println("List the details of branches in a given city.");
                System.out.print("Enter City to retrieve details of each Branch in city: ");
                String addr_city = stdIn.readLine();
                System.out.println();
                String query1 = "select * from Branch where addr_city = '" + addr_city + "'";
                executequery(query1);
                break;
            case 2:
                System.out.println("Find the total number of branches in a given state.");
                System.out.print("Enter State to retrieve the total number of branches: ");
                String addr_st = stdIn.readLine();
                System.out.println();
                String query2 = "select count(branch_num) from Branch where addr_st = '" + addr_st + "'";
                executequery(query2);
                break;
            case 3:
                System.out.println("List name, position, and salary of all employees at a given branch, ordered by name.");
                System.out.print("Enter Branch Number to retrieve information: ");
                int branch_num = Integer.parseInt(stdIn.readLine());
                System.out.println();
                String query3 = "select name,position,salary from Employee where branch_num = " + branch_num + " order by name";
                executequery(query3);
                break;
            case 4:
                System.out.println("The total number of employees and the sum of their salaries:");
                System.out.println();
                String query4 = "select sum(salary), count(emp_num) from Employee";
                executequery(query4);
                break;
            case 5:
                System.out.println("The number of employees in each position at branches in Baltimore, MD.");
                System.out.println();
                String query5 = "select count(emp_num),position from Employee where Employee.branch_num in (select branch_num from Branch where Branch.addr_city = 'Baltimore' and Branch.addr_st = 'Maryland') group by position";
                executequery(query5);
                break;
            case 6:
                System.out.println("The name of branch managers, ordered by branch address:");
                String query6 = "select manager from Branch order by addr_st,addr_city,addr_str";
                executequery(query6);
                break;
            case 7:
                System.out.println("List the names of associates supervised by a given supervisor.");
                System.out.print("Enter name of supervisor (first last):");
                String supervisor = stdIn.readLine();
                String query7 = "select name from Employee where position = 'Associate' and supervisor = '" + supervisor + "'";
                executequery(query7);
                break;
            case 8:
                System.out.println("List the details of properties in a given city, along with their owners’s details,\n\tordered by rent.");
                System.out.print("Enter the city: ");
                addr_city = stdIn.readLine();
                System.out.println();
                String query8 = "select * from Property,PropOwner,PropOwnerTele,PropOwnerFax where Property.owner = PropOwner.name and PropOwner.name = PropOwnerTele.name and PropOwner.name = PropOwnerFax.name and Property.addr_city = '" + addr_city + "' order by Property.rent";
                executequery(query8);
                break;
            case 9:
                System.out.println("List the details of properties for rent assigned to each associate at a given branch.");
                System.out.print("Enter a Branch Number: ");
                branch_num = Integer.parseInt(stdIn.readLine());
                System.out.println();
                String query9 = "select * from Property where property_num in (select property_num from Employee,Lease,works_on where Employee.emp_num = works_on.emp_num and works_on.lease_num = Lease.lease_num and Employee.branch_num = " + branch_num + ")";
                executequery(query9);
                break;
            case 10:
                System.out.println("List the details of properties provided by business owners at a given branch.");
                System.out.print("Enter a Branch Number: ");
                branch_num = Integer.parseInt(stdIn.readLine());
                System.out.println();
                String query10 = "select * from Property where property_num in (select rents.property_num from PropOwner,rents,Lease,works_on,Employee where PropOwner.name = rents.name and rents.property_num = Lease.property_num and Lease.lease_num = works_on.lease_num and works_on.emp_num = Employee.emp_num and Employee.branch_num = " + branch_num + " and PropOwner.private = 'No')";
                execute(query10);
                break;
            case 11:
                System.out.println("Find the total number of properties of each type at all branches.");
                String query11 = "select count(property_num),type from Property group by type";
                executequery(query11);
                break;
            case 12:
                System.out.println("List the details of private property owners that provide more than one property for rent.");
                System.out.println("This query is currently not supported.");
                break;
            case 13:
                System.out.println("List the details of apartments with at least two bedrooms in Baltimore,\n\tMD with a monthly rent of at most $1200.");
                System.out.println();
                String query13 = "select * from Property where type = 'apartment' and bedrooms >= 2 and addr_city = 'Baltimore' and addr_st = 'MD' and rent <= 1200";
                executequery(query13);
                break;
            case 14:
                System.out.println("List the details of clients registered at a branch, together with their preferences,\n\twhich have not signed a lease yet.");
                System.out.println();
                String query14 = "select * from Client where client_num not in (select client_num from obtains)";
                execute(query14);
                break;
            case 15:
                System.out.println("List the details of the owner of a given property.");
                System.out.print("Enter a Property Number: ");
                int property_num = Integer.parseInt(stdIn.readLine());
                System.out.println();
                String query15 = "select * from PropOwner where name in (select name from rents where property_num = " + property_num + ")";
                executequery(query15);
                break;
            case 16:
                System.out.println("List the comments made by clients that viewed a given property.");
                System.out.print("Enter a Property Number:");
                property_num = Integer.parseInt(stdIn.readLine());
                System.out.println();
                String query16 = "select comments from views where property_num = " + property_num;
                executequery(query16);
                break;
            case 17:
                System.out.println("Find those properties that have been advertised more than the average number of times.");
                System.out.println("This query is currently not supported.");
                break;
            case 18:
                System.out.println("List the details of leases due to expire next month at a given branch.");
                System.out.print("Enter a Branch Number: ");
                branch_num = Integer.parseInt(stdIn.readLine());
                System.out.println();
                String query18 = "select * from Lease where enddate < add_months(sysdate,1) and lease_num in (select lease_num from works_on,Employee where works_on.emp_num = Employee.emp_num and Employee.branch_num = " + branch_num + ")";
                executequery(query18);
                break;
            case 19:
                System.out.println("For each state, list the total number of leases with rental duration less than 12 months.");
                String query19 = "select count(lease_num),addr_st from Lease,Property where Lease.property_num = Property.property_num and enddate - startdate < 12 * 31 group by Property.addr_st";
                break;
            case 20:
                System.out.println("Find the total current monthly rental income, total monthly management fees, total salaries,\n\tas well as the maximum possible monthly rental income and management fee.");
                System.out.println();
                String query20a = "select sum(rent),sum(fee) from Property where property_num in (select property_num from Lease)";
                String query20b = "select sum(salary) from (select distinct emp_num,salary from Employee)";
                String query20c = "select sum(rent),sum(fee) from Property";
                executequery(query20a);
                System.out.println();
                executequery(query20b);
                System.out.println();
                executequery(query20c);
                break;
            case 21:
                System.out.println("List the details of properties that have not been rented out for the last three months.");
                String query21 = "select * from Lease,Property where enddate <= add_months(sysdate,-3) and Lease.property_num = Property.property_num";
                executequery(query21);
                break;
            case 22:
                System.out.println("List the details of clients whose preferences match a given property.");
                System.out.print("Enter a Property Number: ");
                property_num = Integer.parseInt(stdIn.readLine());
                System.out.println();
                String query22 = "select * from Client,ClientHomeTele,ClientWorkTele where Client.client_num = ClientHomeTele.client_num and Client.client_num = ClientWorkTele.client_num and preference in (select type from Property where Property.property_num = " + property_num + ")";
                executequery(query22);
                break;
            default:
                System.out.println("Invalid");
                break;
        }
    }
    
    public static void executequery(String sql) {
        
        /* begin sql code stuff */
        try {
            Class.forName("oracle.jdbc.driver.OracleDriver");
        } catch(ClassNotFoundException ex) {
            ex.printStackTrace(System.err);
            System.exit(1);
        }
        String url = "jdbc:oracle:thin:@oracle.gl.umbc.edu:1521:GL";
        Connection con = null;
        try {
            con = DriverManager.getConnection(url, userLogin, userPasswd);
            System.out.println("Connected to Oracle.");
        } catch (SQLException se ){
            System.out.println("Unable to connect to Oracle.");
            se.printStackTrace();
            System.exit(1);
        }
        try {
            /* This part executes whatever was passed to it, completely unprotected */
            Statement stmt = con.createStatement();
            ResultSet rs =  stmt.executeQuery(sql);
            
            /* This next bit prints out all the data returned regardless
             * If a delete or something doesn't want output, then I can just make
             * more than one of these execute things. */
            ResultSetMetaData metadata = rs.getMetaData();
            
            int columns = metadata.getColumnCount();
            int i = 0;
            
            for (i = 1; i < columns + 1; ++i) {
                String columnname = metadata.getColumnLabel(i);
                int display = metadata.getColumnDisplaySize(i);
                
                System.out.print(columnname + "\t");
            }
            System.out.println();
            
            while (rs.next()) {
                for (i = 1; i < columns + 1; ++i) {
                    String data = rs.getString(i);
                    System.out.print(data + "\t");
                }
                System.out.println();
            }
            stmt.close();
        } catch (SQLException ex ){
            System.out.println("Error while executing query.");
            ex.printStackTrace(System.err);
            System.exit(1);
        }
        /* end sql code stuff */
        
    }    
    public static void execute(String sql) {
        try {
            Class.forName("oracle.jdbc.driver.OracleDriver");
        } catch(ClassNotFoundException ex) {
            ex.printStackTrace(System.err);
            System.exit(1);
        }
        
        String url = "jdbc:oracle:thin:@oracle.gl.umbc.edu:1521:GL";
        Connection con = null;
        try {
            con = DriverManager.getConnection(url, userLogin, userPasswd);
            System.out.println("Connected to Oracle.");
        } catch (SQLException se ){
            System.out.println("Unable to connect to Oracle.");
            se.printStackTrace();
            System.exit(1);
        }
        try {
            Statement stmt = con.createStatement();
            stmt.executeUpdate(sql);
            stmt.close();
        } catch (SQLException ex ){
            System.out.println("Error while executing query.");
            ex.printStackTrace(System.err);
            System.exit(1);
        }
    }
    
    public static String userLogin;
    public static String userPasswd;
}