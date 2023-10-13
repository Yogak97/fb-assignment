/*
Author : Yoganand Kanhed
Description : C++ FB client Serializer (For Demonstration only)
*/

#include "client_generated.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace ClientEncoder;

int main(int argc, char *argv[])
{
    flatbuffers::FlatBufferBuilder builder;

    auto personYoga = ClientEncoder::CreatePerson(builder, builder.CreateString("Yoganand"), 21, 76.5, builder.CreateString("Male"));
    auto personBhargav = ClientEncoder::CreatePerson(builder, builder.CreateString("Bhargav"), 24, 80.0, builder.CreateString("Male"));
    auto personChinmay = ClientEncoder::CreatePerson(builder, builder.CreateString("Chinmay"), 23, 75.0, builder.CreateString("Male"));

    auto personMayur = ClientEncoder::CreatePerson(builder, builder.CreateString("Mayur"), 27, 77.5, builder.CreateString("Male"));
    auto personAkshay = ClientEncoder::CreatePerson(builder, builder.CreateString("Akshay"), 24, 90.0, builder.CreateString("Male"));
    auto personAnanya = ClientEncoder::CreatePerson(builder, builder.CreateString("Ananya"), 26, 55.0, builder.CreateString("Female"));

    // std::cout << ClientEncoder::GetPerson(builder, personAnanya)->name()->c_str() << std::endl;
    // std::cout << ClientEncoder::GetPerson(builder, personAnanya)->age() << std::endl;
    // std::cout << ClientEncoder::GetPerson(builder, personAnanya)->weight() << std::endl;

    std::vector<flatbuffers::Offset<Person>> vector_membersOfCoep;
    vector_membersOfCoep.push_back(personYoga);
    vector_membersOfCoep.push_back(personBhargav);
    vector_membersOfCoep.push_back(personChinmay);
    auto membersOfCoep = builder.CreateVector(vector_membersOfCoep);

    auto groupCoep = ClientEncoder::CreateGroup(builder, builder.CreateString("COEP"), 22.6, 77.1, membersOfCoep);
    // std::cout << ClientEncoder::GetGroup(builder, groupCoep)->groupName()->c_str() << std::endl;
    // std::cout << ClientEncoder::GetGroup(builder, groupCoep)->averageAge() << std::endl;
    // std::cout << ClientEncoder::GetGroup(builder, groupCoep)->averageWeight() << std::endl;
    // std::cout << ClientEncoder::GetGroup(builder, groupCoep)->members()->size() << std::endl;

    std::vector<flatbuffers::Offset<Person>> vector_membersOfMit;
    vector_membersOfMit.push_back(personMayur);
    vector_membersOfMit.push_back(personAkshay);
    vector_membersOfMit.push_back(personAnanya);
    auto membersOfMit = builder.CreateVector(vector_membersOfMit);

    auto groupMit = ClientEncoder::CreateGroup(builder, builder.CreateString("MIT"), 25.66, 74.1, membersOfMit);
    // std::cout << ClientEncoder::GetGroup(builder, groupMit)->groupName()->c_str() << std::endl;
    // std::cout << ClientEncoder::GetGroup(builder, groupMit)->averageAge() << std::endl;
    // std::cout << ClientEncoder::GetGroup(builder, groupMit)->averageWeight() << std::endl;
    // std::cout << ClientEncoder::GetGroup(builder, groupMit)->members()->size() << std::endl;

    //*************** By now the Persons and Groups are ready*************
    // Now its time for them to put into container to write into buffer

    std::vector<flatbuffers::Offset<Client>> vector_Clients;
    auto clientPersonYoga = CreateClient(builder, ClientEncoder::ClientUnion_Person, personYoga.Union());
    auto clientGroupCoep = CreateClient(builder, ClientEncoder::ClientUnion_Group, groupCoep.Union());
    auto clientGroupMit = CreateClient(builder, ClientEncoder::ClientUnion_Group, groupMit.Union());
    auto clientPersonBhargav = CreateClient(builder, ClientEncoder::ClientUnion_Person, personBhargav.Union());
    vector_Clients.push_back(clientPersonYoga);
    vector_Clients.push_back(clientGroupCoep);
    vector_Clients.push_back(clientGroupMit);
    vector_Clients.push_back(clientPersonBhargav);
    auto clients = builder.CreateVector(vector_Clients);

    auto clientContainer = CreateClientContainer(builder, clients);
    builder.Finish(clientContainer);

    // Access the serialized data to write into binary file
    const uint8_t *buffer = builder.GetBufferPointer();
    int size = builder.GetSize();

    builder.Reset();

    std::cout << "Size:" << size << std::endl;

    if (buffer && size > 0)
    {
        std::ofstream outfile("fb_clients.bin", std::ios::out | std::ios::binary);

        if (outfile.is_open())
        {
            outfile.write(reinterpret_cast<const char *>(buffer), size);
            outfile.close();
            std::cout << "Data has been written to output.bin." << std::endl;
        }
        else
        {
            std::cerr << "Failed to open the file for writing." << std::endl;
        }
    }
    else
    {
        std::cout << "Buffer was empty" << std::endl;
    }

    return 0;
}