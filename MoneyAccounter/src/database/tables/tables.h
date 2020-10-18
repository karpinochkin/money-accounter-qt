#ifndef TABLES_H
#define TABLES_H

#include <QString>

namespace DB::Tables::Data {

struct CurrencySymbol {
static inline QString tableDB() {
    return "tbl_currency_symbol";
}

static inline QString idColumnDB() {
    return "id";
}

static inline QString symbolColumnDB() {
    return "symbol";
}

static inline QString idCorrencyColumnDB() {
    return "id_currency";
}
};

struct Currency {

static inline QString tableDB() {
    return "tbl_currency";
}

static inline QString idColumnDB() {
    return "id";
}

static inline QString nameColumnDB() {
    return "name";
}
};

struct Icon {
    static inline QString tableDB() {
        return "tbl_icons";
    }

    static inline QString idColumnDB() {
        return "id";
    }

    static inline QString pathColumnDB() {
        return "path";
    }
};

struct CashAccountCategory {
    static inline QString tableDB() {
        return "tbl_cash_acc_categories";
    }

    static inline QString idColumnDB() {
        return "id";
    }

    static inline QString nameColumnDB() {
        return "name";
    }

    static inline QString descriptionColumnDB() {
        return "description";
    }

    static inline QString isIncludeRefundColumnDB() {
        return "is_include_refund";
    }

    static inline QString isIncludeDebtColumnDB() {
        return "is_include_debt";
    }

    static inline QString isIncludePurposeColumnDB() {
        return "is_include_purpose";
    }
};

struct CashAccount {
    static inline QString tableDB() {
        return "tbl_cash_accounts";
    }

    static inline QString idColumnDB() {
        return "id";
    }

    static inline QString nameColumnDB() {
        return "name";
    }

    static inline QString descriptionColumnDB() {
        return "description";
    }

    static inline QString idIconColumnDB() {
        return "id_icon";
    }

    static inline QString colorColumnDB() {
        return "color";
    }

    static inline QString idCurrencyColumnDB() {
        return "id_currency";
    }

    static inline QString displayInOverallBalanceColumnDB() {
        return "display_in_overall_balance";
    }

    static inline QString displayInExpensesColumnDB() {
        return "display_in_expenses";
    }

    static inline QString refundColumnDB() {
        return "refund";
    }

    static inline QString debtColumnDB() {
        return "debt";
    }

    static inline QString balanceColumnDB() {
        return "balance";
    }

    static inline QString purposeColumnDB() {
        return "purpose";
    }

    static inline QString idCashAccountCategoryColumnDB() {
        return "id_cash_acc_category";
    }
};

}

#endif // TABLES_H
