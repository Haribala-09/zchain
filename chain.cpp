#include <fstream>
#include <vector>
#include <memory>
#include <iostream>
#include <ctime>
#include "block.h"

class z_chain
{
private:
    std::vector<std::shared_ptr<z_block>> blocks;

public:
    std::string top_hash()
    {
        return blocks[blocks.size() - 1]->get_c_hash();
    }

    z_chain()
    {
        std::string d = "sriram.";
        std::string h = "0";
        z_block gen(d, h, std::time(nullptr));
        add_block(gen);
    }

    void add_block(z_block &blk)
    {
        blocks.push_back(std::make_shared<z_block>(blk));
    }

    void print_chain()
    {
        for (const auto &blk : blocks)
        {
            std::cout << "---\ndata: " << blk->get_data() << "\nprev hash: " << blk->get_p_hash() << "\ncurr hash: " << blk->get_c_hash() << "\ntimestamp: " << blk->get_timestamp() << "\n---" << std::endl;
        }
    }

    void save_to_file(const std::string &filename)
    {
        std::ofstream ofs(filename);
        if (!ofs)
        {
            std::cerr << "Error in opening file for saving" << '\n';
            return;
        }

        std::cout << "File opened successfully for writing." << std::endl;

        for (const auto &b : blocks)
        {
            // std::cout << "Writing block data: "
            //           << b->get_data() << " "
            //           << b->get_p_hash() << " "
            //           << b->get_c_hash() << " "
            //           << b->get_timestamp() << std::endl;

            ofs << b->get_data() << " " << b->get_p_hash() << " " << b->get_c_hash() << " " << b->get_timestamp() << std::endl;
        }

        ofs.flush();
        if (ofs.fail())
        {
            std::cerr << "Error flushing data to file." << std::endl;
        }

        std::cout << "Chain saved to file!" << std::endl;
    }

    void retrive_from_file(const std::string &filename)
    {
        std::ifstream ifs(filename);

        if (!ifs)
        {
            std::cerr << "Error opening file for reading" << '\n';
            return;
        }

        blocks.clear();

        std::string data, prev_hash, curr_hash;
        time_t timestamp;

        while (ifs >> data >> prev_hash >> curr_hash >> timestamp)
        {
            // std::cout << "Data: " << data << ", Prev Hash: " << prev_hash << ", Curr Hash: " << curr_hash << ", Timestamp: " << timestamp;
            z_block blk(data, prev_hash, curr_hash, timestamp);
            blocks.push_back(std::make_shared<z_block>(blk));
        }

        std::cout << "Blockchain loaded from file" << '\n';
    }
};


// int main()
// {
//     z_chain myfirst;
//     std::string x = "junkie";
//     z_block tmp(x, myfirst.top_hash(), std::time(nullptr));
//     myfirst.add_block(tmp);
//     myfirst.print_chain();

//     // test();
// }
