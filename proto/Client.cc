/* Copyright (c) 2012 Stanford University
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR(S) DISCLAIM ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL AUTHORS BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <endian.h>
#include "proto/Client.h"

namespace LogCabin {
namespace Protocol {
namespace Client {

void
RequestHeaderPrefix::fromBigEndian()
{
    // version is only 1 byte, nothing to flip
}

void
RequestHeaderPrefix::toBigEndian()
{
    // version is only 1 byte, nothing to flip
}

void
RequestHeaderVersion1::fromBigEndian()
{
    // opCode is only 1 byte, nothing to flip
}

void
RequestHeaderVersion1::toBigEndian()
{
    // opCode is only 1 byte, nothing to flip
}

void
ResponseHeaderPrefix::fromBigEndian()
{
    // status is only 1 byte, nothing to flip
}

void
ResponseHeaderPrefix::toBigEndian()
{
    // status is only 1 byte, nothing to flip
}

void
ResponseHeaderVersion1::fromBigEndian()
{
    // no fields, nothing to flip
}

void
ResponseHeaderVersion1::toBigEndian()
{
    // no fields, nothing to flip
}

} // namespace LogCabin::Protocol::Client
} // namespace LogCabin::Protocol
} // namespace LogCabin