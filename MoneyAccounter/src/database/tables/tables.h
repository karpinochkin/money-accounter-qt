#ifndef TABLES_H
#define TABLES_H

#include <QString>

namespace DB::Tables::Data {

struct Currency {

static inline QString tableName() {
    return "tbl_currency";
}

static inline QString id() {
    return "id";
}

static inline QString name() {
    return "name";
}

static inline QString symbol() {
    return "active_symbol";
}
};

struct Icon {
    static inline QString tableName() {
        return "tbl_icons";
    }

    static inline QString id() {
        return "id";
    }

    static inline QString path() {
        return "path";
    }
};

struct CashAccountType {
    static inline QString tableName() {
        return "tbl_cash_acc_categories";
    }

    static inline QString id() {
        return "id";
    }

    static inline QString name() {
        return "name";
    }

    static inline QString description() {
        return "description";
    }

    static inline QString isIncludeRefund() {
        return "is_include_refund";
    }

    static inline QString isIncludeDebt() {
        return "is_include_debt";
    }

    static inline QString isIncludePurpose() {
        return "is_include_purpose";
    }
};

struct CashAccount {
    static inline QString tableName() {
        return "tbl_cash_accounts";
    }

    static inline QString id() {
        return "id";
    }

    static inline QString name() {
        return "name";
    }

    static inline QString description() {
        return "description";
    }

    static inline QString idIcon() {
        return "id_icon";
    }

    static inline QString color() {
        return "color";
    }

    static inline QString idCurrency() {
        return "id_currency";
    }

    static inline QString displayInOverallBalance() {
        return "display_in_overall_balance";
    }

    static inline QString displayInExpenses() {
        return "display_in_expenses";
    }

    static inline QString refund() {
        return "refund";
    }

    static inline QString debt() {
        return "debt";
    }

    static inline QString balance() {
        return "balance";
    }

    static inline QString purpose() {
        return "purpose";
    }

    static inline QString idCashAccountType() {
        return "id_cash_acc_category";
    }
};

struct Category {
    static inline QString tableName() {
        return "tbl_category";
    }

    static inline QString id() {
        return "id";
    }

    static inline QString name() {
        return "name";
    }

    static inline QString description() {
        return "description";
    }

    static inline QString idCurrency() {
        return "id_currency";
    }

    static inline QString idIcon() {
        return "id_icon";
    }

    static inline QString color() {
        return "color";
    }

    static inline QString isActive() {
        return "is_active";
    }
};

struct Transaction {
    static inline QString tableName() {
        return "tbl_transaction";
    }

    static inline QString id() {
        return "id";
    }

    static inline QString name() {
        return "name";
    }

    static inline QString descrpiption() {
        return "description";
    }

    static inline QString idCashAccount() {
        return "id_cash_account";
    }

    static inline QString idCategory() {
        return "id_category";
    }

    static inline QString datetime() {
        return "datetime";
    }

    static inline QString sum() {
        return "amount";
    }
};

}

namespace DB::Tables {

using DataCashAccType = Data::CashAccountType;
using DataCashAcc = Data::CashAccount;
using DataCategory = Tables::Data::Category;
using DataCurrency = Data::Currency;
using DataIcon = Data::Icon;
using DataTransact = Data::Transaction;

}

#endif // TABLES_H
