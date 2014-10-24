#ifndef MOTH_INCLUDE_REPORTER_REPORTER_HPP
#define MOTH_INCLUDE_REPORTER_REPORTER_HPP

namespace moth
{
    namespace reporter
    {
        enum class severity_t
        {
                INFO, DEBUG, WARN, ERROR, DEATH
        };

        inline void check(
                bool a_in_expression_eval, severity_t a_in_severity, const char *a_in_format, ...)
        {
                // TODO:
        }

        inline void report(
                severity_t a_in_severity, const char *a_in_format, ...)
        {
                // TODO:
        }
    }
}

#endif /* MOTH_INCLUDE_REPORTER_REPORTER_HPP */