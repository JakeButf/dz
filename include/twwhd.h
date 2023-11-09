/*

VALUES FROM HERE:
https://docs.google.com/spreadsheets/d/1kloHL2zQztswThTgl3zMrl1hdGh8qb9AgaZWj6Powvw

Credits: Myself, BowserIsBored, CloudModding

*/
#include <cstdint>
#include <string>

#ifndef TWWHD_H
#define TWWHD_H
//Types
typedef struct {
	uint32_t address;
	std::string context;
}twwhd32;

typedef struct {
	uint8_t value;
	std::string context;
}twwhd8;

typedef struct {
    uint32_t address;
    uint32_t value;
}twwhd_flag;

//Pointer Based Structs
struct twwhd_link {
	uint32_t pointer = 0x10989C74;
	uint32_t animation_increment = pointer + 0x57C0; //the animations are read only (there's probably values that actually affect the animations but are unknown)
	uint32_t animation_position = pointer + 0x57BC;
};
const twwhd_link link;

//Pointerless Address' (TODO: Find Pointers)
const static size_t twwhd_scene_flag_elements = (0x15073E18 - 0x15073DF8) / sizeof(uint32_t) + 1;
twwhd_flag twwhd_scene_flags[twwhd_scene_flag_elements] = {
    {0x15073DF8, 0},
    {0x15073DFC, 0},
    {0x15073E00, 0},
    {0x15073E04, 0},
    {0x15073E08, 0},
    {0x15073E0C, 0},
    {0x15073E10, 0},
    {0x15073E14, 0},
    {0x15073E18, 0}
};

const static size_t twwhd_global_flag_elements = (0x15073CE3 - 0x15073CA4) / sizeof(uint32_t) + 1;
twwhd_flag global_flags[twwhd_global_flag_elements] = {
    {0x15073CA4, 0},
    {0x15073CA8, 0},
    {0x15073CAC, 0},
    {0x15073CB0, 0},
    {0x15073CB4, 0},
    {0x15073CB8, 0},
    {0x15073CBC, 0},
    {0x15073CC0, 0},
    {0x15073CC4, 0},
    {0x15073CC8, 0},
    {0x15073CCC, 0},
    {0x15073CD0, 0},
    {0x15073CD4, 0},
    {0x15073CD8, 0},
    {0x15073CDC, 0},
    {0x15073CE0, 0}
};

struct twwhd_items {
    twwhd8 heros_charm = { 0x01, "Hero's Charm" };
    twwhd8 telescope = { 0x20, "Telescope" };
    twwhd8 heros_sword = { 0x38, "Hero's Sword" };
    twwhd8 master_sword = { 0x39, "Master Sword" };
    twwhd8 master_sword_half_restored = { 0x3A, "Master Sword (Half Restored)" };
    twwhd8 master_sword_full_restored = { 0x3E, "Master Sword (Full Restored)" };
    twwhd8 heros_shield = { 0x3B, "Hero's Shield" };
    twwhd8 mirror_shield = { 0x3C, "Mirror Shield" };
    twwhd8 power_bracelets = { 0x28, "Power Bracelets" };
    twwhd8 wind_waker = { 0x22, "Wind Waker" };
    twwhd8 grappling_hook = { 0x25, "Grappling Hook" };
    twwhd8 spoils_bag = { 0x24, "Spoils Bag" };
    twwhd8 boomerang = { 0x2D, "Boomerang" };
    twwhd8 deku_leaf = { 0x34, "Deku Leaf" };
    twwhd8 tingle_bottle = { 0x21, "Tingle Bottle" };
    twwhd8 pictobox = { 0x23, "PictoBox" };
    twwhd8 deluxe_pictobox = { 0x26, "Deluxe PictoBox" };
    twwhd8 iron_boots = { 0x29, "Iron Boots" };
    twwhd8 magic_armor = { 0x2A, "Magic Armor" };
    twwhd8 bait_bag = { 0x2C, "Bait Bag" };
    twwhd8 heros_bow = { 0x27, "Hero's Bow" };
    twwhd8 fire_ice_arrows = { 0x35, "Fire & Ice Arrows" };
    twwhd8 light_arrows = { 0x36, "Light Arrows" };
    twwhd8 bombs = { 0x31, "Bombs" };
    twwhd8 bottle_1 = { 0x50, "Bottle 1" };
    twwhd8 bottle_2 = { 0x50, "Bottle 2" };
    twwhd8 bottle_3 = { 0x50, "Bottle 3" };
    twwhd8 bottle_4 = { 0x50, "Bottle 4" };
    twwhd8 delivery_bag = { 0x30, "Delivery Bag" };
    twwhd8 hookshot = { 0x2F, "Hookshot" };
    twwhd8 skull_hammer = { 0x33, "Skull Hammer" };
    twwhd8 water_boots = { 0x2B, "Water Boots" };
    twwhd8 bare_hand = { 0x2E, "Bare Hand" };
    twwhd8 heros_clothes = { 0x32, "Hero's Clothes" };
    twwhd8 heros_new_clothes = { 0x37, "Hero's New Clothes" };
    twwhd8 heros_sword_dropped = { 0x3D, "Hero's Sword (Dropped)" };
    twwhd8 piece_of_heart_alt_message = { 0x3F, "Piece of Heart (Alt Message)" };
    twwhd8 pirates_charm = { 0x42, "Pirate's Charm" };
    twwhd8 grass_ball = { 0x44, "Grass Ball" };
    twwhd8 skull_necklace = { 0x45, "Skull Necklace" };
    twwhd8 boko_baba_seed = { 0x46, "Boko Baba Seed" };
    twwhd8 golden_feather = { 0x47, "Golden Feather" };
    twwhd8 knights_crest = { 0x48, "Knights Crest" };
    twwhd8 red_chu_jelly = { 0x49, "Red Chu Jelly" };
    twwhd8 green_chu_jelly = { 0x4A, "Green Chu Jelly" };
    twwhd8 blue_chu_jelly = { 0x4B, "Blue Chu Jelly" };
    twwhd8 dungeon_map = { 0x4C, "Dungeon Map" };
    twwhd8 compass = { 0x4D, "Compass" };
    twwhd8 big_key = { 0x4E, "Big Key" };
    twwhd8 empty_bship = { 0x4F, "Empty Bship" };
    twwhd8 red_potion = { 0x51, "Red Potion" };
    twwhd8 green_potion = { 0x52, "Green Potion" };
    twwhd8 blue_potion = { 0x53, "Blue Potion" };
    twwhd8 soup_half = { 0x54, "Soup (Half)" };
    twwhd8 soup = { 0x55, "Soup" };
    twwhd8 water = { 0x56, "Water" };
    twwhd8 fairy = { 0x57, "Fairy" };
    twwhd8 fire_fly = { 0x58, "Fire Fly" };
    twwhd8 magic_water = { 0x59, "Magic Water" };
    twwhd8 triforce_shard_1 = { 0x61, "Triforce Shard 1" };
    twwhd8 triforce_shard_2 = { 0x62, "Triforce Shard 2" };
    twwhd8 triforce_shard_3 = { 0x63, "Triforce Shard 3" };
    twwhd8 triforce_shard_4 = { 0x64, "Triforce Shard 4" };
    twwhd8 triforce_shard_5 = { 0x65, "Triforce Shard 5" };
    twwhd8 triforce_shard_6 = { 0x66, "Triforce Shard 6" };
    twwhd8 triforce_shard_7 = { 0x67, "Triforce Shard 7" };
    twwhd8 triforce_shard_8 = { 0x68, "Triforce Shard 8" };
    twwhd8 nayrus_pearl = { 0x69, "Nayru's Pearl" };
    twwhd8 dins_pearl = { 0x6A, "Din's Pearl" };
    twwhd8 farores_pearl = { 0x6B, "Farore's Pearl" };
    twwhd8 knowledge_tf = { 0x6C, "Knowledge TF" };
    twwhd8 winds_requiem = { 0x6D, "Wind's Requiem" };
    twwhd8 ballad_of_gales = { 0x6E, "Ballad of Gales" };
    twwhd8 command_melody = { 0x6F, "Command Melody" };
    twwhd8 earth_gods_lyric = { 0x70, "Earth God's Lyric" };
    twwhd8 wind_gods_aria = { 0x71, "Wind God's Aria" };
    twwhd8 song_of_passing = { 0x72, "Song of Passing" };
    twwhd8 sail = { 0x78, "Sail" };
    twwhd8 deciphered_triforce_chart_1 = { 0x79, "Deciphered Triforce Chart 1" };
    twwhd8 deciphered_triforce_chart_2 = { 0x7A, "Deciphered Triforce Chart 2" };
    twwhd8 deciphered_triforce_chart_3 = { 0x7B, "Deciphered Triforce Chart 3" };
    twwhd8 deciphered_triforce_chart_4 = { 0x7C, "Deciphered Triforce Chart 4" };
    twwhd8 deciphered_triforce_chart_5 = { 0x7D, "Deciphered Triforce Chart 5" };
    twwhd8 deciphered_triforce_chart_6 = { 0x7E, "Deciphered Triforce Chart 6" };
    twwhd8 deciphered_triforce_chart_7 = { 0x7F, "Deciphered Triforce Chart 7" };
    twwhd8 deciphered_triforce_chart_8 = { 0x80, "Deciphered Triforce Chart 8" };
    twwhd8 bait = { 0x82, "Bait" };
    twwhd8 hyoi_pear = { 0x83, "Hyoi Pear" };
    twwhd8 town_flower = { 0x8C, "Town Flower" };
    twwhd8 sea_flower = { 0x8D, "Sea Flower" };
    twwhd8 exotic_flower = { 0x8E, "Exotic Flower" };
    twwhd8 heros_flag = { 0x8F, "Hero's Flag" };
    twwhd8 big_catch_flag = { 0x90, "Big Catch Flag" };
    twwhd8 big_sale_flag = { 0x91, "Big Sale Flag" };
    twwhd8 pinwheel = { 0x92, "Pinwheel" };
    twwhd8 sickle_moon_flag = { 0x93, "Sickle Moon Flag" };
    twwhd8 skull_tower_idol = { 0x94, "Skull Tower Idol" };
    twwhd8 fountain_idol = { 0x95, "Fountain Idol" };
    twwhd8 postman_statue = { 0x96, "Postman Statue" };
    twwhd8 shop_guru_statue = { 0x97, "Shop Guru Statue" };
    twwhd8 fathers_letter = { 0x98, "Father's Letter" };
    twwhd8 note_to_mom = { 0x99, "Note to Mom" };
    twwhd8 maggies_letter = { 0x9A, "Maggie's Letter" };
    twwhd8 moblins_letter = { 0x9B, "Moblin's Letter" };
    twwhd8 cabana_deed = { 0x9C, "Cabana Deed" };
    twwhd8 complimentary_id = { 0x9D, "Complimentary ID" };
    twwhd8 fill_up_coupon = { 0x9E, "Fill-Up Coupon" };
    twwhd8 legendary_pictograph = { 0x9F, "Legendary Pictograph" };
    twwhd8 dragon_tingle_statue = { 0xA3, "Dragon Tingle Statue" };
    twwhd8 forbidden_tingle_statue = { 0xA4, "Forbidden Tingle Statue" };
    twwhd8 goddess_tingle_statue = { 0xA5, "Goddess Tingle Statue" };
    twwhd8 earth_tingle_statue = { 0xA6, "Earth Tingle Statue" };
    twwhd8 wind_tingle_statue = { 0xA7, "Wind Tingle Statue" };
    twwhd8 hurricane_spin = { 0xAA, "Hurricane Spin" };
    twwhd8 wallet_1000_rupees = { 0xAB, "Wallet (1000 Rupees)" };
    twwhd8 wallet_5000_rupees = { 0xAC, "Wallet (5000 Rupees)" };
    twwhd8 bomb_bag_60 = { 0xAD, "Bomb Bag (60)" };
    twwhd8 bomb_bag_90 = { 0xAE, "Bomb Bag (90)" };
    twwhd8 quiver_60 = { 0xAF, "Quiver (60)" };
    twwhd8 quiver_99 = { 0xB0, "Quiver (99)" };
    twwhd8 double_magic = { 0xB2, "Double Magic" };
    twwhd8 rupee_50 = { 0xB3, "50 Rupees" };
    twwhd8 rupee_100 = { 0xB4, "100 Rupees" };
    twwhd8 rupee_150 = { 0xB5, "150 Rupees" };
    twwhd8 rupee_200 = { 0xB6, "200 Rupees" };
    twwhd8 rupee_250 = { 0xB7, "250 Rupees" };
    twwhd8 rupee_500 = { 0xB8, "500 Rupees" };
    twwhd8 submarine_chart = { 0xC2, "Submarine Chart" };
    twwhd8 beedles_chart = { 0xC3, "Beedle's Chart" };
    twwhd8 platform_chart = { 0xC4, "Platform Chart" };
    twwhd8 light_ring_chart = { 0xC5, "Light Ring Chart" };
    twwhd8 secret_cave_chart = { 0xC6, "Secret Cave Chart" };
    twwhd8 sea_hearts_chart = { 0xC7, "Sea Hearts Chart" };
    twwhd8 island_hearts_chart = { 0xC8, "Island Hearts Chart" };
    twwhd8 great_fairy_chart = { 0xC9, "Great Fairy Chart" };
    twwhd8 octo_chart = { 0xCA, "Octo Chart" };
    twwhd8 incredible_chart = { 0xCB, "INcredible Chart" };
    twwhd8 treasure_chart_7 = { 0xCC, "Treasure Chart 7" };
    twwhd8 treasure_chart_27 = { 0xCD, "Treasure Chart 27" };
    twwhd8 treasure_chart_21 = { 0xCE, "Treasure Chart 21" };
    twwhd8 treasure_chart_13 = { 0xCF, "Treasure Chart 13" };
    twwhd8 treasure_chart_32 = { 0xD0, "Treasure Chart 32" };
    twwhd8 treasure_chart_19 = { 0xD1, "Treasure Chart 19" };
    twwhd8 treasure_chart_41 = { 0xD2, "Treasure Chart 41" };
    twwhd8 treasure_chart_26 = { 0xD3, "Treasure Chart 26" };
    twwhd8 treasure_chart_8 = { 0xD4, "Treasure Chart 8" };
    twwhd8 treasure_chart_37 = { 0xD5, "Treasure Chart 37" };
    twwhd8 treasure_chart_25 = { 0xD6, "Treasure Chart 25" };
    twwhd8 treasure_chart_17 = { 0xD7, "Treasure Chart 17" };
    twwhd8 treasure_chart_36 = { 0xD8, "Treasure Chart 36" };
    twwhd8 treasure_chart_22 = { 0xD9, "Treasure Chart 22" };
    twwhd8 treasure_chart_9 = { 0xDA, "Treasure Chart 9" };
    twwhd8 ghost_ship_chart = { 0xDB, "Ghost Ship Chart" };
    twwhd8 tingles_chart = { 0xDC, "Tingle's Chart" };
    twwhd8 treasure_chart_14 = { 0xDD, "Treasure Chart 14" };
    twwhd8 treasure_chart_10 = { 0xDE, "Treasure Chart 10" };
    twwhd8 treasure_chart_40 = { 0xDF, "Treasure Chart 40" };
    twwhd8 treasure_chart_3 = { 0xE0, "Treasure Chart 3" };
    twwhd8 treasure_chart_4 = { 0xE1, "Treasure Chart 4" };
    twwhd8 treasure_chart_28 = { 0xE2, "Treasure Chart 28" };
    twwhd8 treasure_chart_16 = { 0xE3, "Treasure Chart 16" };
    twwhd8 treasure_chart_18 = { 0xE4, "Treasure Chart 18" };
    twwhd8 treasure_chart_34 = { 0xE5, "Treasure Chart 34" };
    twwhd8 treasure_chart_29 = { 0xE6, "Treasure Chart 29" };
    twwhd8 treasure_chart_1 = { 0xE7, "Treasure Chart 1" };
    twwhd8 treasure_chart_35 = { 0xE8, "Treasure Chart 35" };
    twwhd8 treasure_chart_12 = { 0xE9, "Treasure Chart 12" };
    twwhd8 treasure_chart_6 = { 0xEA, "Treasure Chart 6" };
    twwhd8 treasure_chart_24 = { 0xEB, "Treasure Chart 24" };
    twwhd8 treasure_chart_39 = { 0xEC, "Treasure Chart 39" };
    twwhd8 treasure_chart_38 = { 0xED, "Treasure Chart 38" };
    twwhd8 treasure_chart_2 = { 0xEE, "Treasure Chart 2" };
    twwhd8 treasure_chart_33 = { 0xEF, "Treasure Chart 33" };
    twwhd8 treasure_chart_31 = { 0xF0, "Treasure Chart 31" };
    twwhd8 treasure_chart_23 = { 0xF1, "Treasure Chart 23" };
    twwhd8 treasure_chart_5 = { 0xF2, "Treasure Chart 5" };
    twwhd8 treasure_chart_20 = { 0xF3, "Treasure Chart 20" };
    twwhd8 treasure_chart_30 = { 0xF4, "Treasure Chart 30" };
    twwhd8 treasure_chart_15 = { 0xF5, "Treasure Chart 15" };
    twwhd8 treasure_chart_11 = { 0xF6, "Treasure Chart 11" };
    twwhd8 triforce_chart_8 = { 0xF7, "Triforce Chart 8" };
    twwhd8 triforce_chart_7 = { 0xF8, "Triforce Chart 7" };
    twwhd8 triforce_chart_6 = { 0xF9, "Triforce Chart 6" };
    twwhd8 triforce_chart_5 = { 0xFA, "Triforce Chart 5" };
    twwhd8 triforce_chart_4 = { 0xFB, "Triforce Chart 4" };
    twwhd8 triforce_chart_3 = { 0xFC, "Triforce Chart 3" };
    twwhd8 triforce_chart_2 = { 0xFD, "Triforce Chart 2" };
    twwhd8 triforce_chart_1 = { 0xFE, "Triforce Chart 1" };
    twwhd8 empty_slot = { 0xFF, "Empty Slot" };
};

struct twwhd_item_slots {
    twwhd32 item_inventory_base     = { 0x150736BC, "Inventory Base (Telescope)" };
	twwhd32 telescope			    = { item_inventory_base.address + 0x0, "Telescope Inventory Slot"};
    twwhd32 wind_waker	        	= { item_inventory_base.address + 0x02, "Wind Waker Inventory Slot" };
    twwhd32 grappling_hook	        = { item_inventory_base.address + 0x3, "Grappling Hook Inventory Slot" };
    twwhd32 spoils_bag		        = { item_inventory_base.address + 0x04, "Spoils Bag Inventory Slot" };
    twwhd32 boomerang		    	= { item_inventory_base.address + 0x05, "Boomerang Inventory Slot" };
    twwhd32 deku_leaf		    	= { item_inventory_base.address + 0x06, "Leaf Inventory Slot" };
    twwhd32 tingle_bottle		    = { item_inventory_base.address + 0x07, "Tingle Bottle Inventory Slot" };
    twwhd32 picto_box			    = { item_inventory_base.address + 0x08, "Picto Box Inventory Slot" };
    twwhd32 iron_boots	        	= { item_inventory_base.address + 0x09, "Iron Boots Inventory Slot" };
    twwhd32 magic_armor	        	= { item_inventory_base.address + 0x0A, "Magic Armor Inventory Slot" };
    twwhd32 bait_bag			    = { item_inventory_base.address + 0x0B, "Bait Bag Inventory Slot" };
    twwhd32 heros_bow			    = { item_inventory_base.address + 0x0C, "Hero's Bow Inventory Slot" };
    twwhd32 bombs				    = { item_inventory_base.address + 0x0D, "Bomb Inventory Slot" };
    twwhd32 bottle1			        = { item_inventory_base.address + 0x0E, "Bottle 1 Inventory Slot" };
    twwhd32 bottle2			        = { item_inventory_base.address + 0x0F, "Bottle 2 Inventory Slot" };
    twwhd32 bottle3			        = { item_inventory_base.address + 0x10, "Bottle 3 Inventory Slot" };
    twwhd32 bottle4			        = { item_inventory_base.address + 0x11, "Bottle 4 Inventory Slot" };
    twwhd32 delivery_bag		    = { item_inventory_base.address + 0x12, "Delivery Bag Inventory Slot" };
    twwhd32 hookshot			    = { item_inventory_base.address + 0x13, "Hookshot Inventory Slot" };
    twwhd32 skull_hammer		    = { item_inventory_base.address + 0x14, "Skull Hammer Inventory Slot" };
};

struct twwhd_item_amounts {
    twwhd32 item_amounts_base = { 0x150736EA, "Item Amounts Base (Bombs)" };
    twwhd32 bombs =     { item_amounts_base.address + 0x0, "Bomb Ammo Count" };
    twwhd32 arrows =    { item_amounts_base.address + 0x1, "Arrow Ammo Count" };
};


//Free Address
twwhd32 twwhd_current_hearts =    { 0x15073683, "Current Hearts" };
twwhd32 twwhd_max_hearts =        { 0x15073681, "Max Hearts" };
twwhd32 twwhd_next_stage =        { 0x109763F0, "Next Stage" };
twwhd32 twwhd_next_room =         { 0x109763FA, "Next Room" };
twwhd32 twwhd_next_spawn =        { 0x109763F9, "Next Spawn" };
twwhd32 twwhd_next_layer =        { 0x109763FB, "Next Layer" };
twwhd32 twwhd_get_item_value =    { 0x10976554, "Get Item Value" };

const twwhd_item_slots item_slots;
const twwhd_items items;
const twwhd_item_amounts item_amounts;

twwhd8 TWWHD_GetItemForSlot(twwhd32 slot)
{
        if (item_slots.telescope.address == slot.address)
            return items.telescope;
        if (item_slots.wind_waker.address == slot.address)
            return items.wind_waker;
        if (item_slots.grappling_hook.address == slot.address)
            return items.grappling_hook;
        if (item_slots.spoils_bag.address == slot.address)
            return items.spoils_bag;
        if (item_slots.boomerang.address == slot.address)
            return items.boomerang;
        if (item_slots.deku_leaf.address == slot.address)
            return items.deku_leaf;
        if (item_slots.tingle_bottle.address == slot.address)
            return items.tingle_bottle;
        if (item_slots.picto_box.address == slot.address)
            return items.pictobox;
        if (item_slots.iron_boots.address == slot.address)
            return items.iron_boots;
        if (item_slots.magic_armor.address == slot.address)
            return items.magic_armor;
        if (item_slots.bait_bag.address == slot.address)
            return items.bait_bag;
        if (item_slots.heros_bow.address == slot.address)
            return items.heros_bow;
        if (item_slots.bombs.address == slot.address)
            return items.bombs;
        if (item_slots.bottle1.address == slot.address)
            return items.bottle_1;
        if (item_slots.bottle2.address == slot.address)
            return items.bottle_2;
        if (item_slots.bottle3.address == slot.address)
            return items.bottle_3;
        if (item_slots.bottle4.address == slot.address)
            return items.bottle_4;
        if (item_slots.delivery_bag.address == slot.address)
            return items.delivery_bag;
        if (item_slots.hookshot.address == slot.address)
            return items.hookshot;
        if (item_slots.skull_hammer.address == slot.address)
            return items.skull_hammer;
}

#endif