int main() {
  try {
    /* Configuration for framework: example.
            to exit - input 7 ,
            to perform child1 action - input 2,
            performing child2 action - disabled
            to perform child3 action - input 4,
            performing child4 action - disabled
    */
    std::vector<int> selectorConfig({7, 2, -1, 4});

    /* Set framework with configuration. */
    using UPtrFrameworkIf = std::unique_ptr<CFrameworkIf>;
    UPtrFrameworkIf framework;

    framework = UPtrFrameworkIf(CFrameworkIf::createNew(&selectorConfig));
    /* Use option below to use simple selector (simple hardcoded switch)
       instead the complex one
    */
    // framework = UPtrFrameworkIf(CFrameworkIf::createNew(nullptr));

    /* Mock input - vector represents input sequence */
    CInput input;
    input.init(new std::vector<int>{2, 4, 3, 8, 0, 7});

    framework->mainLoop(input);

  } catch (const char* result) {
    printf("%s.\n", result);
    fflush(NULL);
    return 0;
  } catch (...) {
    printf("FATAL ERROR! Unhandled exception.");
    return 1;
  }

  return 0;
}