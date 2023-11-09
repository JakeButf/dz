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
typedef struct {
	const uint32_t pointer = 0x10989C74;
	const uint32_t animation_increment = pointer + 0x57C0; //the animations are read only (there's probably values that actually affect the animations but are unknown)
	const uint32_t animation_position = pointer + 0x57BC;
}twwhd_link;

//Pointerless Address' (TODO: Find Pointers)
constexpr size_t twwhd_scene_flag_elements = (0x15073E18 - 0x15073DF8) / sizeof(uint32_t) + 1;
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

constexpr size_t twwhd_global_flag_elements = (0x15073CE3 - 0x15073CA4) / sizeof(uint32_t) + 1;
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

typedef protected struct {
    const twwhd8 heros_charm = { 0x01, "Hero's Charm" };
    const twwhd8 telescope = { 0x20, "Telescope" };
    const twwhd8 heros_sword = { 0x38, "Hero's Sword" };
    const twwhd8 master_sword = { 0x39, "Master Sword" };
    const twwhd8 master_sword_half_restored = { 0x3A, "Master Sword (Half Restored)" };
    const twwhd8 master_sword_full_restored = { 0x3E, "Master Sword (Full Restored)" };
    const twwhd8 heros_shield = { 0x3B, "Hero's Shield" };
    const twwhd8 mirror_shield = { 0x3C, "Mirror Shield" };
    const twwhd8 power_bracelets = { 0x28, "Power Bracelets" };
    const twwhd8 wind_waker = { 0x22, "Wind Waker" };
    const twwhd8 grappling_hook = { 0x25, "Grappling Hook" };
    const twwhd8 spoils_bag = { 0x24, "Spoils Bag" };
    const twwhd8 boomerang = { 0x2D, "Boomerang" };
    const twwhd8 deku_leaf = { 0x34, "Deku Leaf" };
    const twwhd8 tingle_bottle = { 0x21, "Tingle Bottle" };
    const twwhd8 pictobox = { 0x23, "PictoBox" };
    const twwhd8 deluxe_pictobox = { 0x26, "Deluxe PictoBox" };
    const twwhd8 iron_boots = { 0x29, "Iron Boots" };
    const twwhd8 magic_armor = { 0x2A, "Magic Armor" };
    const twwhd8 bait_bag = { 0x2C, "Bait Bag" };
    const twwhd8 heros_bow = { 0x27, "Hero's Bow" };
    const twwhd8 fire_ice_arrows = { 0x35, "Fire & Ice Arrows" };
    const twwhd8 light_arrows = { 0x36, "Light Arrows" };
    const twwhd8 bombs = { 0x31, "Bombs" };
    const twwhd8 bottle_1 = { 0x50, "Bottle 1" };
    const twwhd8 bottle_2 = { 0x50, "Bottle 2" };
    const twwhd8 bottle_3 = { 0x50, "Bottle 3" };
    const twwhd8 bottle_4 = { 0x50, "Bottle 4" };
    const twwhd8 delivery_bag = { 0x30, "Delivery Bag" };
    const twwhd8 hookshot = { 0x2F, "Hookshot" };
    const twwhd8 skull_hammer = { 0x33, "Skull Hammer" };
    const twwhd8 water_boots = { 0x2B, "Water Boots" };
    const twwhd8 bare_hand = { 0x2E, "Bare Hand" };
    const twwhd8 heros_clothes = { 0x32, "Hero's Clothes" };
    const twwhd8 heros_new_clothes = { 0x37, "Hero's New Clothes" };
    const twwhd8 heros_sword_dropped = { 0x3D, "Hero's Sword (Dropped)" };
    const twwhd8 piece_of_heart_alt_message = { 0x3F, "Piece of Heart (Alt Message)" };
    const twwhd8 pirates_charm = { 0x42, "Pirate's Charm" };
    const twwhd8 grass_ball = { 0x44, "Grass Ball" };
    const twwhd8 skull_necklace = { 0x45, "Skull Necklace" };
    const twwhd8 boko_baba_seed = { 0x46, "Boko Baba Seed" };
    const twwhd8 golden_feather = { 0x47, "Golden Feather" };
    const twwhd8 knights_crest = { 0x48, "Knights Crest" };
    const twwhd8 red_chu_jelly = { 0x49, "Red Chu Jelly" };
    const twwhd8 green_chu_jelly = { 0x4A, "Green Chu Jelly" };
    const twwhd8 blue_chu_jelly = { 0x4B, "Blue Chu Jelly" };
    const twwhd8 dungeon_map = { 0x4C, "Dungeon Map" };
    const twwhd8 compass = { 0x4D, "Compass" };
    const twwhd8 big_key = { 0x4E, "Big Key" };
    const twwhd8 empty_bship = { 0x4F, "Empty Bship" };
    const twwhd8 red_potion = { 0x51, "Red Potion" };
    const twwhd8 green_potion = { 0x52, "Green Potion" };
    const twwhd8 blue_potion = { 0x53, "Blue Potion" };
    const twwhd8 soup_half = { 0x54, "Soup (Half)" };
    const twwhd8 soup = { 0x55, "Soup" };
    const twwhd8 water = { 0x56, "Water" };
    const twwhd8 fairy = { 0x57, "Fairy" };
    const twwhd8 fire_fly = { 0x58, "Fire Fly" };
    const twwhd8 magic_water = { 0x59, "Magic Water" };
    const twwhd8 triforce_shard_1 = { 0x61, "Triforce Shard 1" };
    const twwhd8 triforce_shard_2 = { 0x62, "Triforce Shard 2" };
    const twwhd8 triforce_shard_3 = { 0x63, "Triforce Shard 3" };
    const twwhd8 triforce_shard_4 = { 0x64, "Triforce Shard 4" };
    const twwhd8 triforce_shard_5 = { 0x65, "Triforce Shard 5" };
    const twwhd8 triforce_shard_6 = { 0x66, "Triforce Shard 6" };
    const twwhd8 triforce_shard_7 = { 0x67, "Triforce Shard 7" };
    const twwhd8 triforce_shard_8 = { 0x68, "Triforce Shard 8" };
    const twwhd8 nayrus_pearl = { 0x69, "Nayru's Pearl" };
    const twwhd8 dins_pearl = { 0x6A, "Din's Pearl" };
    const twwhd8 farores_pearl = { 0x6B, "Farore's Pearl" };
    const twwhd8 knowledge_tf = { 0x6C, "Knowledge TF" };
    const twwhd8 winds_requiem = { 0x6D, "Wind's Requiem" };
    const twwhd8 ballad_of_gales = { 0x6E, "Ballad of Gales" };
    const twwhd8 command_melody = { 0x6F, "Command Melody" };
    const twwhd8 earth_gods_lyric = { 0x70, "Earth God's Lyric" };
    const twwhd8 wind_gods_aria = { 0x71, "Wind God's Aria" };
    const twwhd8 song_of_passing = { 0x72, "Song of Passing" };
    const twwhd8 sail = { 0x78, "Sail" };
    const twwhd8 deciphered_triforce_chart_1 = { 0x79, "Deciphered Triforce Chart 1" };
    const twwhd8 deciphered_triforce_chart_2 = { 0x7A, "Deciphered Triforce Chart 2" };
    const twwhd8 deciphered_triforce_chart_3 = { 0x7B, "Deciphered Triforce Chart 3" };
    const twwhd8 deciphered_triforce_chart_4 = { 0x7C, "Deciphered Triforce Chart 4" };
    const twwhd8 deciphered_triforce_chart_5 = { 0x7D, "Deciphered Triforce Chart 5" };
    const twwhd8 deciphered_triforce_chart_6 = { 0x7E, "Deciphered Triforce Chart 6" };
    const twwhd8 deciphered_triforce_chart_7 = { 0x7F, "Deciphered Triforce Chart 7" };
    const twwhd8 deciphered_triforce_chart_8 = { 0x80, "Deciphered Triforce Chart 8" };
    const twwhd8 bait = { 0x82, "Bait" };
    const twwhd8 hyoi_pear = { 0x83, "Hyoi Pear" };
    const twwhd8 town_flower = { 0x8C, "Town Flower" };
    const twwhd8 sea_flower = { 0x8D, "Sea Flower" };
    const twwhd8 exotic_flower = { 0x8E, "Exotic Flower" };
    const twwhd8 heros_flag = { 0x8F, "Hero's Flag" };
    const twwhd8 big_catch_flag = { 0x90, "Big Catch Flag" };
    const twwhd8 big_sale_flag = { 0x91, "Big Sale Flag" };
    const twwhd8 pinwheel = { 0x92, "Pinwheel" };
    const twwhd8 sickle_moon_flag = { 0x93, "Sickle Moon Flag" };
    const twwhd8 skull_tower_idol = { 0x94, "Skull Tower Idol" };
    const twwhd8 fountain_idol = { 0x95, "Fountain Idol" };
    const twwhd8 postman_statue = { 0x96, "Postman Statue" };
    const twwhd8 shop_guru_statue = { 0x97, "Shop Guru Statue" };
    const twwhd8 fathers_letter = { 0x98, "Father's Letter" };
    const twwhd8 note_to_mom = { 0x99, "Note to Mom" };
    const twwhd8 maggies_letter = { 0x9A, "Maggie's Letter" };
    const twwhd8 moblins_letter = { 0x9B, "Moblin's Letter" };
    const twwhd8 cabana_deed = { 0x9C, "Cabana Deed" };
    const twwhd8 complimentary_id = { 0x9D, "Complimentary ID" };
    const twwhd8 fill_up_coupon = { 0x9E, "Fill-Up Coupon" };
    const twwhd8 legendary_pictograph = { 0x9F, "Legendary Pictograph" };
    const twwhd8 dragon_tingle_statue = { 0xA3, "Dragon Tingle Statue" };
    const twwhd8 forbidden_tingle_statue = { 0xA4, "Forbidden Tingle Statue" };
    const twwhd8 goddess_tingle_statue = { 0xA5, "Goddess Tingle Statue" };
    const twwhd8 earth_tingle_statue = { 0xA6, "Earth Tingle Statue" };
    const twwhd8 wind_tingle_statue = { 0xA7, "Wind Tingle Statue" };
    const twwhd8 hurricane_spin = { 0xAA, "Hurricane Spin" };
    const twwhd8 wallet_1000_rupees = { 0xAB, "Wallet (1000 Rupees)" };
    const twwhd8 wallet_5000_rupees = { 0xAC, "Wallet (5000 Rupees)" };
    const twwhd8 bomb_bag_60 = { 0xAD, "Bomb Bag (60)" };
    const twwhd8 bomb_bag_90 = { 0xAE, "Bomb Bag (90)" };
    const twwhd8 quiver_60 = { 0xAF, "Quiver (60)" };
    const twwhd8 quiver_99 = { 0xB0, "Quiver (99)" };
    const twwhd8 double_magic = { 0xB2, "Double Magic" };
    const twwhd8 rupee_50 = { 0xB3, "50 Rupees" };
    const twwhd8 rupee_100 = { 0xB4, "100 Rupees" };
    const twwhd8 rupee_150 = { 0xB5, "150 Rupees" };
    const twwhd8 rupee_200 = { 0xB6, "200 Rupees" };
    const twwhd8 rupee_250 = { 0xB7, "250 Rupees" };
    const twwhd8 rupee_500 = { 0xB8, "500 Rupees" };
    const twwhd8 submarine_chart = { 0xC2, "Submarine Chart" };
    const twwhd8 beedles_chart = { 0xC3, "Beedle's Chart" };
    const twwhd8 platform_chart = { 0xC4, "Platform Chart" };
    const twwhd8 light_ring_chart = { 0xC5, "Light Ring Chart" };
    const twwhd8 secret_cave_chart = { 0xC6, "Secret Cave Chart" };
    const twwhd8 sea_hearts_chart = { 0xC7, "Sea Hearts Chart" };
    const twwhd8 island_hearts_chart = { 0xC8, "Island Hearts Chart" };
    const twwhd8 great_fairy_chart = { 0xC9, "Great Fairy Chart" };
    const twwhd8 octo_chart = { 0xCA, "Octo Chart" };
    const twwhd8 incredible_chart = { 0xCB, "INcredible Chart" };
    const twwhd8 treasure_chart_7 = { 0xCC, "Treasure Chart 7" };
    const twwhd8 treasure_chart_27 = { 0xCD, "Treasure Chart 27" };
    const twwhd8 treasure_chart_21 = { 0xCE, "Treasure Chart 21" };
    const twwhd8 treasure_chart_13 = { 0xCF, "Treasure Chart 13" };
    const twwhd8 treasure_chart_32 = { 0xD0, "Treasure Chart 32" };
    const twwhd8 treasure_chart_19 = { 0xD1, "Treasure Chart 19" };
    const twwhd8 treasure_chart_41 = { 0xD2, "Treasure Chart 41" };
    const twwhd8 treasure_chart_26 = { 0xD3, "Treasure Chart 26" };
    const twwhd8 treasure_chart_8 = { 0xD4, "Treasure Chart 8" };
    const twwhd8 treasure_chart_37 = { 0xD5, "Treasure Chart 37" };
    const twwhd8 treasure_chart_25 = { 0xD6, "Treasure Chart 25" };
    const twwhd8 treasure_chart_17 = { 0xD7, "Treasure Chart 17" };
    const twwhd8 treasure_chart_36 = { 0xD8, "Treasure Chart 36" };
    const twwhd8 treasure_chart_22 = { 0xD9, "Treasure Chart 22" };
    const twwhd8 treasure_chart_9 = { 0xDA, "Treasure Chart 9" };
    const twwhd8 ghost_ship_chart = { 0xDB, "Ghost Ship Chart" };
    const twwhd8 tingles_chart = { 0xDC, "Tingle's Chart" };
    const twwhd8 treasure_chart_14 = { 0xDD, "Treasure Chart 14" };
    const twwhd8 treasure_chart_10 = { 0xDE, "Treasure Chart 10" };
    const twwhd8 treasure_chart_40 = { 0xDF, "Treasure Chart 40" };
    const twwhd8 treasure_chart_3 = { 0xE0, "Treasure Chart 3" };
    const twwhd8 treasure_chart_4 = { 0xE1, "Treasure Chart 4" };
    const twwhd8 treasure_chart_28 = { 0xE2, "Treasure Chart 28" };
    const twwhd8 treasure_chart_16 = { 0xE3, "Treasure Chart 16" };
    const twwhd8 treasure_chart_18 = { 0xE4, "Treasure Chart 18" };
    const twwhd8 treasure_chart_34 = { 0xE5, "Treasure Chart 34" };
    const twwhd8 treasure_chart_29 = { 0xE6, "Treasure Chart 29" };
    const twwhd8 treasure_chart_1 = { 0xE7, "Treasure Chart 1" };
    const twwhd8 treasure_chart_35 = { 0xE8, "Treasure Chart 35" };
    const twwhd8 treasure_chart_12 = { 0xE9, "Treasure Chart 12" };
    const twwhd8 treasure_chart_6 = { 0xEA, "Treasure Chart 6" };
    const twwhd8 treasure_chart_24 = { 0xEB, "Treasure Chart 24" };
    const twwhd8 treasure_chart_39 = { 0xEC, "Treasure Chart 39" };
    const twwhd8 treasure_chart_38 = { 0xED, "Treasure Chart 38" };
    const twwhd8 treasure_chart_2 = { 0xEE, "Treasure Chart 2" };
    const twwhd8 treasure_chart_33 = { 0xEF, "Treasure Chart 33" };
    const twwhd8 treasure_chart_31 = { 0xF0, "Treasure Chart 31" };
    const twwhd8 treasure_chart_23 = { 0xF1, "Treasure Chart 23" };
    const twwhd8 treasure_chart_5 = { 0xF2, "Treasure Chart 5" };
    const twwhd8 treasure_chart_20 = { 0xF3, "Treasure Chart 20" };
    const twwhd8 treasure_chart_30 = { 0xF4, "Treasure Chart 30" };
    const twwhd8 treasure_chart_15 = { 0xF5, "Treasure Chart 15" };
    const twwhd8 treasure_chart_11 = { 0xF6, "Treasure Chart 11" };
    const twwhd8 triforce_chart_8 = { 0xF7, "Triforce Chart 8" };
    const twwhd8 triforce_chart_7 = { 0xF8, "Triforce Chart 7" };
    const twwhd8 triforce_chart_6 = { 0xF9, "Triforce Chart 6" };
    const twwhd8 triforce_chart_5 = { 0xFA, "Triforce Chart 5" };
    const twwhd8 triforce_chart_4 = { 0xFB, "Triforce Chart 4" };
    const twwhd8 triforce_chart_3 = { 0xFC, "Triforce Chart 3" };
    const twwhd8 triforce_chart_2 = { 0xFD, "Triforce Chart 2" };
    const twwhd8 triforce_chart_1 = { 0xFE, "Triforce Chart 1" };
    const twwhd8 empty_slot = { 0xFF, "Empty Slot" };
}twwhd_items;

const twwhd32 item_inventory_base = { 0x150736BC, "Inventory Base (Telescope)" };
typedef protected struct {	
	const twwhd32 telescope			    = { item_inventory_base.address + 0x0, "Telescope Inventory Slot"};
    const twwhd32 wind_waker	    	= { item_inventory_base.address + 0x02, "Wind Waker Inventory Slot" };
    const twwhd32 grappling_hook	    = { item_inventory_base.address + 0x03, "Grappling Hook Inventory Slot" };
    const twwhd32 spoils_bag		    = { item_inventory_base.address + 0x04, "Spoils Bag Inventory Slot" };
    const twwhd32 boomerang		    	= { item_inventory_base.address + 0x05, "Boomerang Inventory Slot" };
    const twwhd32 deku_leaf		    	= { item_inventory_base.address + 0x06, "Leaf Inventory Slot" };
    const twwhd32 tingle_bottle		    = { item_inventory_base.address + 0x07, "Tingle Bottle Inventory Slot" };
    const twwhd32 picto_box			    = { item_inventory_base.address + 0x08, "Picto Box Inventory Slot" };
    const twwhd32 iron_boots	    	= { item_inventory_base.address + 0x09, "Iron Boots Inventory Slot" };
    const twwhd32 magic_armor	    	= { item_inventory_base.address + 0x0A, "Magic Armor Inventory Slot" };
    const twwhd32 bait_bag			    = { item_inventory_base.address + 0x0B, "Bait Bag Inventory Slot" };
    const twwhd32 heros_bow			    = { item_inventory_base.address + 0x0C, "Hero's Bow Inventory Slot" };
    const twwhd32 bombs				    = { item_inventory_base.address + 0x0D, "Bomb Inventory Slot" };
    const twwhd32 bottle1			    = { item_inventory_base.address + 0x0E, "Bottle 1 Inventory Slot" };
    const twwhd32 bottle2			    = { item_inventory_base.address + 0x0F, "Bottle 2 Inventory Slot" };
    const twwhd32 bottle3			    = { item_inventory_base.address + 0x10, "Bottle 3 Inventory Slot" };
    const twwhd32 bottle4			    = { item_inventory_base.address + 0x11, "Bottle 4 Inventory Slot" };
    const twwhd32 delivery_bag		    = { item_inventory_base.address + 0x12, "Delivery Bag Inventory Slot" };
    const twwhd32 hookshot			    = { item_inventory_base.address + 0x13, "Hookshot Inventory Slot" };
    const twwhd32 skull_hammer		    = { item_inventory_base.address + 0x14, "Skull Hammer Inventory Slot" };
}twwhd_item_slots;

const twwhd32 item_amounts_base = { 0x150736EA, "Item Amounts Base (Bombs)" };
typedef protected struct {
    twwhd32 bombs =     { item_amounts_base.address + 0x0, "Bomb Ammo Count" };
    twwhd32 arrows =    { item_amounts_base.address + 0x1, "Arrow Ammo Count" };
}twwhd_item_amounts;

//Free Address
const twwhd32 twwhd_current_hearts =    { 0x15073683, "Current Hearts" };
const twwhd32 twwhd_max_hearts =        { 0x15073681, "Max Hearts" };
const twwhd32 twwhd_next_stage =        { 0x109763F0, "Next Stage" };
const twwhd32 twwhd_next_room =         { 0x109763FA, "Next Room" };
const twwhd32 twwhd_next_spawn =        { 0x109763F9, "Next Spawn" };
const twwhd32 twwhd_next_layer =        { 0x109763FB, "Next Layer" };
const twwhd32 twwhd_get_item_value =    { 0x10976554, "Get Item Value" };


class TWWHD {
public:
	const twwhd_item_slots twwhd_item_slots;
    const twwhd_items twwhd_items;

    twwhd8 TWWHD_GetItemForSlot(twwhd32 slot)
    {
        if (twwhd_item_slots.telescope.address == slot.address)
            return twwhd_items.telescope;
        if (twwhd_item_slots.wind_waker.address == slot.address)
            return twwhd_items.wind_waker;
        if (twwhd_item_slots.grappling_hook.address == slot.address)
            return twwhd_items.grappling_hook;
        if (twwhd_item_slots.spoils_bag.address == slot.address)
            return twwhd_items.spoils_bag;
        if (twwhd_item_slots.boomerang.address == slot.address)
            return twwhd_items.boomerang;
        if (twwhd_item_slots.deku_leaf.address == slot.address)
            return twwhd_items.deku_leaf;
        if (twwhd_item_slots.tingle_bottle.address == slot.address)
            return twwhd_items.tingle_bottle;
        if (twwhd_item_slots.picto_box.address == slot.address)
            return twwhd_items.pictobox;
        if (twwhd_item_slots.iron_boots.address == slot.address)
            return twwhd_items.iron_boots;
        if (twwhd_item_slots.magic_armor.address == slot.address)
            return twwhd_items.magic_armor;
        if (twwhd_item_slots.bait_bag.address == slot.address)
            return twwhd_items.bait_bag;
        if (twwhd_item_slots.heros_bow.address == slot.address)
            return twwhd_items.heros_bow;
        if (twwhd_item_slots.bombs.address == slot.address)
            return twwhd_items.bombs;
        if (twwhd_item_slots.bottle1.address == slot.address)
            return twwhd_items.bottle_1;
        if (twwhd_item_slots.bottle2.address == slot.address)
            return twwhd_items.bottle_2;
        if (twwhd_item_slots.bottle3.address == slot.address)
            return twwhd_items.bottle_3;
        if (twwhd_item_slots.bottle4.address == slot.address)
            return twwhd_items.bottle_4;
        if (twwhd_item_slots.delivery_bag.address == slot.address)
            return twwhd_items.delivery_bag;
        if (twwhd_item_slots.hookshot.address == slot.address)
            return twwhd_items.hookshot;
        if (twwhd_item_slots.skull_hammer.address == slot.address)
            return twwhd_items.skull_hammer;
    }
};

#endif