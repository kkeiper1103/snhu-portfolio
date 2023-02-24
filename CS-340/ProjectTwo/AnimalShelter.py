from pymongo import MongoClient
from bson.objectid import ObjectId
import json

class AnimalShelter(object):
    """ CRUD operations for Animal collection in MongoDB """

    def __init__(self, username, password):
        # Initializing the MongoClient. This helps to 
        # access the MongoDB databases and collections. 
        # the aacuser account is defined on the admin database, not aac. it's like calling --authenticationDatabase "admin"
        self.client = MongoClient('mongodb://%s:%s@localhost:46255/admin' % (username, password))
        # where xxxx is your unique port number
        self.database = self.client['aac']

# Complete this create method to implement the C in CRUD.
    def create(self, data):
        if data is not None:
            # changed to insert_one since insert is deprecated
            return self.database.animals.insert_one(data)  # data should be dictionary 
            
        else:
            raise Exception("Nothing to save, because data parameter is empty")

# Create method to implement the R in CRUD. 
    def read(self, data):
        if data is not None:
            return self.database.animals.find(data, {"_id": False})
        else:
            raise Exception("No Query Parameters Given")
            
    # this method will update as many records as what match the parameters in existing
    # will add/merge the values in newValues into the existing object
    def update(self, data, newValues):
        if data is None:
            raise Exception("Cannot UPDATE without limiting parameters")
            
        if newValues is None:
            raise Exception("Must have new Values to Set")
           
        results = self.database.animals.update_many(data, { "$set": newValues })
        
        return json.dumps({
            "results": {
                "count": results.modified_count
            }
        })
        
    # deletes records from the database where the values match what is found in data
    def delete(self, data):
        if data is None:
            raise Exception("Can't DELETE without parameters")
            
        results = self.database.animals.delete_many(data)
            
        return json.dumps({
            "results": {
                "count": results.deleted_count
            }
        })