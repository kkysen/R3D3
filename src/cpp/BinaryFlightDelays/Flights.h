//
// Created by Khyber on 4/5/2018.
//

#ifndef BINARYFLIGHTDELAYS_FLIGHTS_H
#define BINARYFLIGHTDELAYS_FLIGHTS_H

#include <streambuf>

#include <emscripten/fetch.h>
#include <future>

#include "CompactFlight.h"

namespace r3d3 {
    
    class Flights final {
    
    private:
        
        static const size_t DAYS_IN_YEAR = 365; // for 2015
        
        using NumFlightsInDay = u16; // large enough for num flights on every day
        
        using FlightsInDay = std::vector<CompactFlight>;
        
        static NumFlightsInDay numFlightsInDay(FlightsInDay flightsInDay);
        
        using Array = std::array<FlightsInDay, DAYS_IN_YEAR>;
        
        // TODO make this a pointer and use RAII
        
        const Array flights;
        
        // TODO should Array flights be passed by reference, or will copying be elided?
        
        explicit Flights(Array flights) noexcept;
        
        static Array convert(std::streambuf& buf) noexcept;
        
        static std::streambuf& convert(const emscripten_fetch_t& fetch) noexcept;
        
        static bool startedLoading = false;
        static std::promise<const Flights&> promise;
        
        static const u32 MAX_FAILS = 10;
        static u32 numFails = 0;
        
        static void load(std::string url) noexcept;
    
    public:
        
        static const std::string FETCH_ROUTE = "/data/flights";
        
        void serialize(std::streambuf& buf) const noexcept;
        
        explicit Flights(std::streambuf& buf) noexcept;
        
        explicit Flights(const emscripten_fetch_t& fetch) noexcept;
        
        static std::future<const Flights&> get(std::string url = FETCH_ROUTE) noexcept;
        
        /*
         * For performance sake, instead of using JS to iterate over the flights,
         * filter them, and compute things based on them,
         * there will be an exported method here
         * that takes filter, callback, etc. functions/expressions.
         *
         * It will act like a mini-interpreter, like an SQL engine,
         * and will allow C++/wasm to compute things significantly faster
         * and much more memory efficiently.
         *
         * In some cases, this will just be calling a normal JS function from wasm,
         * but in cases where the inputs are restricted,
         * it's much easier to optimize/compile/interpret.
         */
        
        // TODO
        
    };
    
};


#endif //BINARYFLIGHTDELAYS_FLIGHTS_H
