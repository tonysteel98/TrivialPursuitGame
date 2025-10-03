#pragma once

class DeleteManagerTest {
public:
    // Test deleting a row that exists.
    void Test1_InteractiveDeletion();

    // Test attempting to delete a row that does NOT exist.
    void Test2_InteractiveNonExistentDeletion();
};
