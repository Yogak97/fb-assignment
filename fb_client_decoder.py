# Python Deserializer (for demonstration purpose only)
#Author : Yoganand Kanhed

import os, sys
sys.path.append(os.path.join(os.path.dirname(__file__), '../flatbuffers/python'))
import ClientEncoder.ClientContainer
import ClientEncoder.Group 
import ClientEncoder.Client
import ClientEncoder.ClientUnion
import ClientEncoder.Person


# Function to deserialize binary data
def deserialize_binary_file(file_path):
    # Read binary data from file
    with open(file_path, "rb") as file:
        data = file.read()

    # Deserialize binary data using flatbuffers
    client_container = ClientEncoder.ClientContainer.ClientContainer.GetRootAsClientContainer(data, 0)
    for i in range(client_container.ClientsLength()):
        client = client_container.Clients(i).Client()
        client_type = client_container.Clients(i).ClientType()

        if client_type == ClientEncoder.ClientUnion.ClientUnion().Person :
            print("***************************Person********************")
            
            person = ClientEncoder.Person.Person()
            person.Init(client.Bytes, client.Pos)

            print(f"Name: {person.Name().decode('utf-8')}")
            print(f"Age: {person.Age()}")
            print(f"Weight: {person.Weight()}")
            print(f"Gender: {person.Gender().decode('utf-8')}")
        elif client_type == ClientEncoder.ClientUnion.ClientUnion().Group:
            print("*************************Group************************")

            group = ClientEncoder.Group.Group();
            group.Init(client.Bytes, client.Pos)

            print(f"Group Name: {group.GroupName().decode('utf-8')}")
            print(f"Average Age: {group.AverageAge()}")
            print(f"Average Weight: {group.AverageWeight()}")

            print("Members:")

            for j in range(group.MembersLength()):
                person = group.Members(j)
                print(f"  Name: {person.Name().decode('utf-8')}")
                print(f"  Age: {person.Age()}")
                print(f"  Weight: {person.Weight()}")
                print(f"  Gender: {person.Gender().decode('utf-8')}")
                print("------------------------")
        else:
            print("Unknown Type")

# Usage example
if __name__ == "__main__":
    binary_file_path = "fb_clients.bin"
    deserialize_binary_file(binary_file_path)
