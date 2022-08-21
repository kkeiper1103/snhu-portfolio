package com.gnarlyweb.contactService;

import static org.junit.jupiter.api.Assertions.*;

import com.gnarlyweb.contactService.Contact;
import org.junit.jupiter.api.Test;

import com.gnarlyweb.contactService.Exceptions.InvalidArgumentException;

import org.junit.jupiter.api.*;

public class ContactTest {
	
	protected Contact testedContact;
	
	@BeforeEach
	void setup() throws Exception {
		this.testedContact = new Contact("001", "Kyle", "Keiper", "1234567890", "123 Example Way");
	}

	/**
	 * ID Field Constraints - <= 10 chars, not null, not updatable
	 */
	
	@Test
	void testIdCannotBeLongerThanTenCharacters() {
		
		assertThrows(InvalidArgumentException.class, () -> {
			new Contact("ThisStringIsTooLong", "Kyle", "Invalid", "invalid", "invalid");
		});
	}
	
	@Test
	void testIdCannotBeNull() {
		assertThrows(InvalidArgumentException.class, () -> {
			new Contact(null, "Kyle", "Keiper", "1234567890", "123 address");
		});
	}
	
	@Test
	void testIdCannotBeUpdated() {
		assertThrows(Exception.class, () -> {
			this.testedContact.setId("Cannot Be Updated");
		});
	}
	
	/**
	 * FirstName Constraints - <= 10 chars, not null
	 */
	@Test
	void testFirstNameShorterThanTenCharacters() {
		assertThrows(InvalidArgumentException.class, () -> {
			new Contact("002", "KyleKeiperSuperLongName", "Invalid", "invalid", "invalid");
		});
	}
	
	@Test
	void testFirstNameCannotBeNull() {
		assertThrows(Exception.class, () -> {
			new Contact("002", null, "Invalid", "invalid", "invalid");
		});
	}
	
	/**
	 * LastName Constraints - <= 10 chars, not null
	 */
	@Test
	void testLastNameShorterThanTenCharacters() {
		assertThrows(InvalidArgumentException.class, () -> {
			new Contact("002", "Kyle", "ThisLastNameIsTooLong", "invalid", "invalid");
		});
	}
	
	@Test
	void testLastNameCannotBeNull() {
		assertThrows(Exception.class, () -> {
			new Contact("002", "Kyle", null, "invalid", "invalid");
		});
	}
	
	/**
	 * Phone Constraints
	 * 
	 * Not Null
	 * Exactly 10 Characters
	 */
	@Test
	void testPhoneCannotBeNull() {
		assertThrows(Exception.class, () -> {
			new Contact("002", "Kyle", "Keiper", null, "invalid");
		});
	}
	
	@Test
	void testPhoneMustBeTenCharactersLong() {
		Exception e = assertThrows(InvalidArgumentException.class, () -> {
			this.testedContact.setPhone("123");
		});
		assertTrue(e.getMessage() == "Phone Number Too Short");
		
		// make sure no exception is thrown when valid
		String newPhone = "5556667777";
		assertDoesNotThrow(() -> {
			this.testedContact.setPhone(newPhone);
		});
		assertTrue(this.testedContact.getPhone() == newPhone);
		
		e = assertThrows(InvalidArgumentException.class, () -> {
			this.testedContact.setPhone("12345678901234567890");
		});
		assertTrue(e.getMessage() == "Phone Number Too Long");
	}
	
	/**
	 * Address Field Constraints
	 * 
	 * Not Null
	 * <= 30 Characters
	 */
	@Test
	void testAddressNotNull() {
		assertThrows(Exception.class, () -> {
			this.testedContact.setAddress(null);
		});
	}
	
	@Test
	void testAddressNotLongerThan30Characters() {
		String invalidAddress = """
123456 Invalid Address Way
NonExistent City, Bad State,
9992830-293
				""";
		assertThrows(InvalidArgumentException.class, () -> {
			this.testedContact.setAddress(invalidAddress);
		});
	}
}
