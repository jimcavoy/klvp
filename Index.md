# klvp {#mainpage}

Key-Length-Value (KLV) parser library (klvp) provides classes to allow client applications to parse or encode
a KLV encoded metadata stream based on the following STANAG 4609 standards:

- MISB ST 0601, UAS Datalink Local Set 
- MISB ST 0102, Security Metadata Universal and Local Sets for Motion Imagery Data

## Project Structure
The __klvp__ project consists of two static libraries and an example application.

### Static Libraries
The project builds two libraries:

- @ref ./klvp/README.md - KLV parser and encoder library
- @ref ./ldsdb/README.md - Local Dataset (LDS) database library 

### Example Application (klv2xml)
The example application, __klv2xml__, consumes the project's libraries to read a KLV encoded metadata stream and output an XML representation.