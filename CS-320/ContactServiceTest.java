package com.gnarlyweb.contactService;

import static org.junit.jupiter.api.Assertions.*;

import com.gnarlyweb.contactService.ContactService;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class ContactServiceTest {
	
	protected ContactService service = null;
	
	@BeforeEach
	void setupApplication() {
		this.service = ContactService.instance();
	}

	
	/**
	 * Service Should Be Able to Add Contact As Long as ID is Unique
	 */
	@Test
	void testAddsOnlyUniqueIDContacts() throws Exception {
		Contact kyle = new Contact("001", "Kyle", "Keiper", "2345429930", "5835 Example Way");
		
		assertEquals(0, this.service.count());
		
		// make sure kyle is added
		this.service.add(kyle);
		assertEquals(1, this.service.count());
		
		// make sure kyle can't be added again
		this.service.add(kyle);
		assertEquals(1, this.service.count());
		
		// make sure new contact with same ID can't be added
		Contact bubba = new Contact("001", "Bubba", "Gump", "1234567890", "123 Example");
		this.service.add(bubba);
		
		assertEquals(1, this.service.count());
		
		// make sure KYLE is returned for 001, not BUBBA
		assertEquals(kyle, this.service.get("001"));
	}
	
	/**
	 * Service should be able to delete by id
	 */
	@Test
	void testCanDeleteContactsById() throws Exception {
		Contact kyle = new Contact("001", "Kyle", "Keiper", "2345429930", "5835 Example Way");
		
		this.service.add(kyle);
		assertEquals(1, this.service.count());
		
		// delete by id
		Contact deleted = this.service.delete(kyle.getId());
		assertEquals(0, this.service.count());
		
		// make sure the deleted record's ID is the same as kyle's ID
		assertEquals(kyle.getId(), deleted.getId());
	}
	
	/**
	 * Should be able to update fields by providing ID
	 */
	@Test
	void testAbleToUpdateFieldsWithIDGiven() throws Exception {
		Contact kyle = new Contact("001", "Kyle", "Keiper", "2345429930", "5835 Example Way");
		this.service.add(kyle);

		// make sure first name is updated to Kevin
		this.service.updateFirstName("001", "Kevin");
		assertEquals("Kevin", this.service.get("001").getFirstName());
		

		// make sure that last name is now Kelper
		this.service.updateLastName("001", "Kelper");
		assertEquals("Kelper", this.service.get("001").getLastName());
		

		// make sure phone gets changed
		this.service.updatePhone("001", "1112223333");
		assertEquals("1112223333", this.service.get("001").getPhone());
		

		// ensure address is different now
		this.service.updateAddress("001", "789 Example Lane");
		assertEquals("789 Example Lane", this.service.get("001").getAddress());
	}

}
