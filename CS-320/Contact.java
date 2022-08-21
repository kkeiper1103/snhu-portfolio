package com.gnarlyweb.contactService;

import com.gnarlyweb.contactService.Exceptions.InvalidArgumentException;

public class Contact {
	protected String id = null;
	protected String firstName;
	protected String lastName;
	protected String phone;
	protected String address;
	
	public Contact(String id, String firstName, String lastName, String phone, String address) throws Exception {
		this.setId(id);
		this.setFirstName(firstName);
		this.setLastName(lastName);
		this.setPhone(phone);
		this.setAddress(address);
	}
	
	public String getId() {
		return id;
	}
	
	public void setId(String id) throws Exception {
		if(id == null)
			throw new InvalidArgumentException("ID Must Not Be Null");
		
		if(id.length() > 10)
			throw new InvalidArgumentException("ID Cannot Be Longer Than 10 Characters");
		
		if(this.id != null) 
			throw new Exception("ID Cannot Be Updated Once Assigned");
		
		this.id = id;
	}
	
	public String getFirstName() {
		return firstName;
	}
	
	public void setFirstName(String firstName) throws Exception {
		if(firstName == null) throw new Exception("First Name Cannot Be Null");
		
		if(firstName.length() > 10) throw new InvalidArgumentException("First Name Must Be Less Than 11 Characters");
		
		this.firstName = firstName;
	}
	
	public String getLastName() {
		return lastName;
	}
	public void setLastName(String lastName) throws Exception {
		if(lastName == null) throw new Exception("lastName Cannot Be Null");
		
		if(lastName.length() > 10) throw new InvalidArgumentException("lastName Must Be Less Than 11 Characters");
		
		this.lastName = lastName;
	}
	
	public String getPhone() {
		return phone;
	}
	public void setPhone(String phone) throws Exception {
		if(phone == null) throw new Exception("Phone Cannot Be Null");
		
		if(phone.length() < 10) throw new InvalidArgumentException("Phone Number Too Short");
		if(phone.length() > 10) throw new InvalidArgumentException("Phone Number Too Long");
		
		this.phone = phone;
	}
	
	public String getAddress() {
		return address;
	}
	public void setAddress(String address) throws Exception {
		if(address == null) throw new Exception("Address Cannot Be Null");
		
		if(address.length() > 30) throw new InvalidArgumentException("Address Must Be No More Than 30 Characters");
		this.address = address;
	}

	
	
}
