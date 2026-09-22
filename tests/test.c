#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../src/system/store.h"

// One global call-log so we can verify exact call sequence and catch any
// cross-stage bleed (a system firing under the wrong stage).
static char call_log[256][64];
static int  call_log_count = 0;

#define LOG(name) do { \
    snprintf(call_log[call_log_count++], 64, "%s", name); \
} while (0)

// --- PRE_UPDATE ---
void pre_a() { LOG("pre_a"); }
void pre_b() { LOG("pre_b"); }

// --- UPDATE ---
void upd_a() { LOG("upd_a"); }
void upd_b() { LOG("upd_b"); }
void upd_c() { LOG("upd_c"); }

// --- POST_UPDATE ---
void post_a() { LOG("post_a"); }

// --- PRE_FIXED_UPDATE / FIXED_UPDATE / POST_FIXED_UPDATE ---
void pre_fixed_a()  { LOG("pre_fixed_a"); }
void fixed_a()       { LOG("fixed_a"); }
void fixed_b()        { LOG("fixed_b"); }
void post_fixed_a()  { LOG("post_fixed_a"); }

// --- PRE_RENDER / RENDER / POST_RENDER ---
void pre_render_a()  { LOG("pre_render_a"); }
void render_a()      { LOG("render_a"); }
void post_render_a() { LOG("post_render_a"); }

void expect(const char* name) {
    assert(call_log_count > 0);
    // shift check: compare and consume from the front
    static int check_index = 0;
    if (strcmp(call_log[check_index], name) != 0) {
        fprintf(stderr, "MISMATCH at %d: expected '%s', got '%s'\n",
                check_index, name, call_log[check_index]);
        abort();
    }
    printf("OK: %s\n", call_log[check_index]);
    check_index++;
}

int main() {
    SystemStore store = systemstore_create();

    // Register deliberately interleaved / out of enum order to catch
    // any "assumes systems are registered in stage order" bugs.
    systemstore_register(&store, UPDATE, upd_a);
    systemstore_register(&store, PRE_UPDATE, pre_a);
    systemstore_register(&store, POST_UPDATE, post_a);
    systemstore_register(&store, UPDATE, upd_b);
    systemstore_register(&store, PRE_FIXED_UPDATE, pre_fixed_a);
    systemstore_register(&store, FIXED_UPDATE, fixed_a);
    systemstore_register(&store, PRE_UPDATE, pre_b);
    systemstore_register(&store, FIXED_UPDATE, fixed_b);
    systemstore_register(&store, POST_FIXED_UPDATE, post_fixed_a);
    systemstore_register(&store, UPDATE, upd_c);
    systemstore_register(&store, PRE_RENDER, pre_render_a);
    systemstore_register(&store, RENDER, render_a);
    systemstore_register(&store, POST_RENDER, post_render_a);

    // Run every stage, in the real intended app order
    systemstore_run(&store, PRE_UPDATE);
    systemstore_run(&store, UPDATE);
    systemstore_run(&store, POST_UPDATE);
    systemstore_run(&store, PRE_FIXED_UPDATE);
    systemstore_run(&store, FIXED_UPDATE);
    systemstore_run(&store, POST_FIXED_UPDATE);
    systemstore_run(&store, PRE_RENDER);
    systemstore_run(&store, RENDER);
    systemstore_run(&store, POST_RENDER);

    printf("\n--- verifying exact call order ---\n");
    expect("pre_a");
    expect("pre_b");
    expect("upd_a");
    expect("upd_b");
    expect("upd_c");
    expect("post_a");
    expect("pre_fixed_a");
    expect("fixed_a");
    expect("fixed_b");
    expect("post_fixed_a");
    expect("pre_render_a");
    expect("render_a");
    expect("post_render_a");

    assert(call_log_count == 13);
    printf("\nALL STAGES CORRECT — %d calls, no cross-stage bleed\n", call_log_count);
    return 0;
}
