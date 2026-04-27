/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** print_arg_output
*/

#include <unistd.h>
#include <stdio.h>

#include "game.h"
#include "wolf3d.h"

void printd(char *text, int speed)
{
    for (int i = 0; text[i] != '\0'; i++) {
        write(1, &text[i], 1);
        fflush(stdout);
        usleep(speed);
    }
}

int print_help(void)
{
    printd("PROJECT\n    Duckenstein\n\n", W_FAST);
    printd("USAGE\n    ./wolf3d [-h] [-lore]\n\n", W_FAST);
    printd("DESCRIPTION\n    -h display help text\n", W_FAST);
    printd("    -lore display game lore\n", W_FAST);
    return SUCCESS;
}

void print_lore_core_1(void)
{
    printd("Operation: \"Froid de Canard\"\n17 January 1944\n\n", W_SLOW);
    printd("After the Churchill-De Gaulle public speech on ", W_BASIC);
    printd("Jan. 12th, a secret meeting between them took place.\n", W_BASIC);
    printd("They discussed raiding Italy with the allies ", W_BASIC);
    printd("on Jan. 22nd. They call it Operation Shingle.\n\n", W_BASIC);
    printd("Unfortunately, the files containing every detail", W_BASIC);
    printd(" of this mission landed on dirty German hands.\n\n", W_BASIC);
    printd("This is why you're here. ", W_BASIC);
    printd("We want you to get those files back, by ", W_BASIC);
    printd("any way.\n\n", W_SLOW);
    usleep(750000);
    printd("We injected you some kind of super-soldier serum.\n", W_BASIC);
    printd("You are visibly strong enough to handle it but beware, ", W_BASIC);
    printd("some side effect may appear during your mission.\n", W_BASIC);
    usleep(300000);
    printd("We used duck blood to boost your condition", W_BASIC);
    printd(" and resistance, so maybe some side effects", W_BASIC);
    printd(" will be related to this animal.\n", W_BASIC);
}

void print_lore_core_2(void)
{
    usleep(400000);
    printd("But hey !", W_BASIC);
    usleep(400000);
    printd(" Don't worry.", W_BASIC);
    usleep(400000);
    printd(" Wings won't grow on your back.", W_BASIC);
    usleep(400000);
    printd(" I guess", W_BASIC);
    printd("...", W_SLOW);
    usleep(500000);
    printd("\n\nAnyway. Your mission, ", W_BASIC);
    usleep(250000);
    printd("should you choose to accept it", W_BASIC);
    usleep(250000);
    printd(", is to find the files and either bring them back", W_BASIC);
    printd(" or destroy them.\n", W_BASIC);
    usleep(750000);
    printd("*tv off*\n\n", W_FAST);
}

int print_lore(void)
{
    printd("PROJECT : DUCKENSTEIN\n\n", W_FAST);
    printd("Welcome agent X, we were waiting for ", W_BASIC);
    printd("you to wake up from your surgery.\n", W_BASIC);
    usleep(1500000);
    printd("You don't remember everything ?", W_BASIC);
    usleep(400000);
    printd(" No problem we planned a brief in case it happened :", W_BASIC);
    printd(" *tv on*\n\n\n", W_FAST);
    usleep(750000);
    print_lore_core_1();
    print_lore_core_2();
    usleep(750000);
    printd("Good luck proud French soldier", W_BASIC);
    usleep(400000);
    printd(", you will need some.\n", W_BASIC);
    return SUCCESS;
}
