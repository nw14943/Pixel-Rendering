//#include <glm/glm.hpp>
//
//
//{
//    // input
//    // -----
//    processInput(window);
//
//    // render
//    // ------
//    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // bind textures on corresponding texture units
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, texture1);
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, texture2);
//
//    // activate shader
//    ourShader.use();
//
//    // create transformations
//    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    glm::mat4 view = glm::mat4(1.0f);
//    glm::mat4 projection = glm::mat4(1.0f);
//    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//    // retrieve the matrix uniform locations
//    unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
//    unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
//    // pass them to the shaders (3 different ways)
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
//    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
//    ourShader.setMat4("projection", projection);
//
//    // render container
//    glBindVertexArray(VAO);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//    // -------------------------------------------------------------------------------
//    glfwSwapBuffers(window);
//    glfwPollEvents();
//    }