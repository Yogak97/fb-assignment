# fb-assignment

Flatbuffer C++ Serializer and Python Deserializer.

Important Notes:

1. The flatbuffer serializer is written in C++(fb_client_encoder.cpp), the schema(client.fbs) and genrated headers(client_generated.h) for the same are already provided, so no need to genrate it again using flatc. For Demonstration purpose 4 objects are written in the order ( Person -> Group -> Group -> Person) into the buffer.

2. The flatbuffer Deserializer is written in Python(fb_client_decoder.py), it reads the binary buffer file genrated in step 1 and deserialise it. The schema is provided(client.fbs) along with genrated python class files(see ClientEncoder directory).


Please follow below steps to successfully compile the files and run the program (see output directory for output screenshots) :

1. Clone this repository somewhere in your system.
   
       git clone https://github.com/Yogak97/fb-assignment.git

2.     git pull origin main

3. Intialise and update the flatbuffers submodule
   
       git submodule update --init --recursive

Step 4 to 7 are optional jump to step 8 in case you dont wish to build the `flatc` execuatable.

4.     cd flatbuffers

5.     cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release

6.     make -j4

7.     cd ..
   (To get back to the main repo root directory fb-assignment)

8.     g++ -I"flatbuffers/include" fb_client_encoder.cpp -o fb_client_encoder;
   
       ./fb_client_encoder <bin filepath>
   
   Here the `<bin filepath>` is intended binary file path for writing the flatbuffer.
   This step will serialize the data and creates a buffer file.

10.     python3 fb_client_decoder.py <bin filepath>
    
    Here, the  `<bin filepath>` is the same file genrated in step 8.
    This step will deserialize the data and print it in human readable format on the terminal/console.

Optionally to create a JSON file(see fb_clients.json) out of the `<bin filepath>` run the following command:

      ./flatbuffers/flatc --json --raw-binary client.fbs -- <bin filepath>         
