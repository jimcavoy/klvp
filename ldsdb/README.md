Main Page {#mainpage}
=========

# LDS Database (ldsdb)

The Local Dataset (LDS) database (**ldsdb**) library provides classes to allow client applications to query a sqlite3 database.
The sqlite3 database, **klv.s3db**, contains definitions for KLV elements specified in: 

- MISB ST 0601, UAS Datalink Local Set 
- MISB ST 0102, Security Metadata Universal and Local Sets for Motion Imagery Data

The sqlite3 database, **klv.s3db**, is located in the project root directory in the **data** folder.

## Project Structure

Project creates a static library called **ldsdb**. Static library consist of one header file (@ref include/ldsdb/ldsdb.h "ldsdb.h") and one source file (@ref src/ldsdb.cpp "ldsdb.cpp").


