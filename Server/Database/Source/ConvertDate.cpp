#include "ConvertDate.h"


namespace Server::Database
{

    Poco::DateTime Convert(const date::year_month_day& data)
    {
        int year(data.year());
        unsigned int month(data.month());
        unsigned int day(data.day());

        if (year == 0)
        {
            month = 1;
            day = 1;
        }

        return Poco::DateTime(year, month, day);
    };

    date::year_month_day Convert(const Poco::DateTime& data)
    {
        date::month month(data.month());
        date::day day(data.day());

        if(data.year() == 0)
        {
            month = date::month(1);
            day = date::day(1);
        }

        return date::year_month_day(
            date::year(data.year()),
            month,
            day
        );
    };

}