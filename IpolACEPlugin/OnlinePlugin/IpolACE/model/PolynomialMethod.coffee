#
class PolynomialMethod extends Model
    constructor: () ->
        super()

        @add_attr
            _name   : "Polynomial"
            _degree : new Choice(0,["3","5","7","9","11"])
        
        @add_attr
            degree : @_degree
    
    toString: () ->
        @_name.get()
    