package com.gnarlyweb.contactService;

import java.util.ArrayList;

public class ContactService {
	protected ArrayList<Contact> contacts;
	
	static private ContactService _instance = null;
	
	/**
	 * Make the Service class a singleton
	 * @return
	 */
	static public ContactService instance() {
		if(_instance == null)
			_instance = new ContactService();
		
		return _instance;
	}
	
	private ContactService() {
		contacts = new ArrayList<>();
	}
	
	/**
	 * 
	 * @return
	 */
	public int count() {
		return contacts.size();
	}
	
	/**
	 * 
	 * @param contact
	 * @return
	 */
	public boolean add(Contact contact) {
		// if a contact with the given id already exists, don't add
		if(get(contact.getId()) != null) return false;
			
		contacts.add(contact);
		
		return true;
	}
	
	/**
	 * 
	 * @param id
	 * @return
	 */
	public Contact get(String id) {
		// if we find the contact with given ID, return it
		for(Contact c: contacts) {
			if(c.getId() == id) return c;
		}
		
		return null;
	}
	
	/**
	 * 
	 * @param id
	 */
	public Contact delete(String id) {
		for(Contact c: contacts) {
			// if we find a matching contact, remove it and return control
			if(c.getId() == id) {
				contacts.remove(c);
				
				return c;
			}
		}
		
		return null;
	}
	
	// these are the update methods
	public void updateFirstName(String id, String newFirstName) throws Exception {
		if(get(id) != null) get(id).setFirstName(newFirstName);
	}
	
	public void updateLastName(String id, String newLastName) throws Exception {
		if(get(id) != null) get(id).setLastName(newLastName);
	}
	
	public void updatePhone(String id, String newPhone) throws Exception {
		if(get(id) != null) get(id).setPhone(newPhone);
	}
	
	public void updateAddress(String id, String newAddress) throws Exception {
		if(get(id) != null) get(id).setAddress(newAddress);
	}
}
