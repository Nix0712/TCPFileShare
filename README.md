### **Simple File Sharing Using TCP Connection**

*Note: This project is currently a work in progress.*

#### **1. How to Build?**

To get started, ensure that **CMake** and **Make** are installed on your system. Follow these steps to build the project:

1. Create a `build` directory inside the project folder:
   ```bash
   mkdir build
   ```
2. Navigate to the `build` directory:
   ```bash
   cd build
   ```
3. Generate the build files using CMake:
   ```bash
   cmake ..
   ```
4. Compile the project using Make:
   ```bash
   make
   ```

After completing these steps, you will find two executable files in the `build` directory:  
- **TCBShare-Server**  
- **TCBShare-Client**

---

#### **2. Running the Application**

1. Start the **server** by running the `TCBShare-Server` executable:
   ```bash
   ./TCBShare-Server
   ```
2. In another terminal, start the **client** by running the `TCBShare-Client` executable:
   ```bash
   ./TCBShare-Client
   ```

Once both the server and client are running, the client will successfully receive the shared file or message from the server. 🎉
